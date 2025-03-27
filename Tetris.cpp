#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;
const string EMPTY = "  ";

// Tetromino shapes and colors
const string COLORS[7] = {"🟦", "🟨", "🟪", "🟩", "🟥", "🟧", "⬜"};
const int tetrominoes[7][4][4] = {
    {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
    {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // O
    {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // T
    {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // S
    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // Z
    {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // J
    {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}  // L
};

class Tetromino {
public:
    int shape[4][4];
    int x, y;
    string color;

    Tetromino(int type) : color(COLORS[type]) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = tetrominoes[type][i][j];
        x = WIDTH / 2 - 2;
        y = 0;
    }

    void rotate() {
        int temp[4][4] = {0};
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                temp[j][3 - i] = shape[i][j];

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = temp[i][j];
    }
};

class GameBoard {
public:
    string grid[HEIGHT][WIDTH];
    int score;
    int level;
    int linesCleared;

    GameBoard() : score(0), level(1), linesCleared(0) {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                grid[i][j] = EMPTY;
    }

    void draw(Tetromino &t) {
        cout << "\033[H\033[J"; // Clear screen
        for (int i = 0; i < HEIGHT; i++) {
            cout << "|";
            for (int j = 0; j < WIDTH; j++) {
                string displayChar = grid[i][j];

                for (int ti = 0; ti < 4; ti++)
                    for (int tj = 0; tj < 4; tj++)
                        if (t.shape[ti][tj] && (i == t.y + ti) && (j == t.x + tj))
                            displayChar = t.color;

                cout << displayChar;
            }
            cout << "|\n";
        }
        cout << " ";
        for (int i = 0; i < WIDTH; i++) cout << "--";
        cout << " \n";
        cout << "Score: " << score << "  Level: " << level << "  Lines: " << linesCleared << "\n";
        cout << "[A] Left  [D] Right  [S] Down  [W] Rotate  [Space] Hard Drop  [P] Pause  [R] Restart  [X] Exit\n";
    }

    bool canMove(Tetromino &t, int dx, int dy) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (t.shape[i][j]) {
                    int newX = t.x + j + dx;
                    int newY = t.y + i + dy;
                    if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || (newY >= 0 && grid[newY][newX] != EMPTY))
                        return false;
                }
        return true;
    }

    void placeTetromino(Tetromino &t) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (t.shape[i][j])
                    grid[t.y + i][t.x + j] = t.color;
        clearLines();
    }

    void clearLines() {
        int fullLines = 0;
        for (int i = 0; i < HEIGHT; i++) {
            bool full = true;
            for (int j = 0; j < WIDTH; j++)
                if (grid[i][j] == EMPTY) full = false;

            if (full) {
                fullLines++;
                for (int k = i; k > 0; k--)
                    for (int j = 0; j < WIDTH; j++)
                        grid[k][j] = grid[k - 1][j];

                for (int j = 0; j < WIDTH; j++)
                    grid[0][j] = EMPTY;
            }
        }
        score += fullLines == 1 ? 100 : fullLines == 2 ? 300 : fullLines == 3 ? 500 : fullLines == 4 ? 800 : 0;
        linesCleared += fullLines;
        if (linesCleared >= level * 10) level++;
    }
};

class TetrisGame {
public:
    GameBoard board;
    Tetromino *currentPiece;

    TetrisGame() { currentPiece = new Tetromino(rand() % 7); }

    void run() {
        while (true) {
            board.draw(*currentPiece);
            usleep(500000 / board.level);
            update();
        }
    }

    void update() {
        if (!board.canMove(*currentPiece, 0, 1)) {
            board.placeTetromino(*currentPiece);
            delete currentPiece;
            currentPiece = new Tetromino(rand() % 7);
        } else {
            currentPiece->y++;
        }
    }
};

int main() {
    srand(time(0));
    TetrisGame game;
    game.run();
    return 0;
}
