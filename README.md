# Tetris.cpp
A simple terminal-based Tetris game implemented in C++ with Unicode colored blocks for the Tetromino shapes. The game includes basic features like moving Tetrominoes, rotating them, hard dropping, pausing, restarting, and handling the game-over condition.

Features:
7 Tetromino shapes: I, O, T, S, Z, J, L.
Unicode colored blocks for Tetromino shapes.
Basic controls: Move Tetrominoes left, right, down, rotate, and hard drop.
Pause and resume the game with the 'P' key.
Restart the game with the 'R' key.
Game over condition: When a new Tetromino cannot be placed at the top of the board, the game ends.
Terminal-based interface: The game runs in the terminal, rendering the game board with colored Unicode blocks.
Controls:
[A]: Move the current Tetromino left.
[D]: Move the current Tetromino right.
[S]: Move the current Tetromino down.
[W]: Rotate the current Tetromino.
[Space]: Hard drop the current Tetromino.
[P]: Pause the game. Press 'P' again to resume.
[R]: Restart the game.
[X]: Exit the game.
How the Game Works:
The game starts with a random Tetromino falling from the top of the screen.
Players can move the Tetrominoes left, right, down using the arrow keys or the designated keys (A, D, S).
Players can rotate the Tetromino using the W key and hard drop it using the Space key.
Once a Tetromino reaches the bottom of the screen or collides with other blocks, it is placed on the board.
New Tetrominoes are generated randomly after each placement.
The game ends when a new Tetromino cannot be placed because the board is full.
The player can pause the game by pressing the P key and resume it by pressing P again.
Compilation and Running the Game:
On Linux/macOS:
Install a C++ compiler (e.g., g++).
Compile the program:
g++ -std=c++17 -o tetris tetris.cpp
Run the game:

./tetris

On Windows: Install a C++ compiler (e.g., MinGW, Visual Studio, or MSYS2).

Compile the program:

g++ -o tetris tetris.cpp

Run the game:

tetris.exe Code Explanation: Tetromino Class: Represents a Tetromino with its shape, position (x, y), and color.

The rotate() function allows rotating the Tetromino 90 degrees clockwise.

The shape is stored as a 4x4 matrix, where each 1 represents a block of the Tetromino and 0 is empty space.

GameBoard Class: Contains a grid representing the game board.

The draw() function clears the terminal screen and renders the game board along with the current Tetromino.

The canMove() function checks if a Tetromino can be moved to a given position without collision.

The placeTetromino() function places the Tetromino on the grid when it can't move anymore.

TetrisGame Class: Manages the game logic, including user input, updating the game state, and rendering.

The handleInput() function processes keypresses for movement, rotation, and other controls.

The update() function checks if the Tetromino can move down and places it if it cannot.

The hardDrop() function makes the Tetromino fall directly to the bottom of the board.

The restartGame() function clears the board and starts a new game.

Terminal Input Handling: The game uses termios for non-blocking input and to disable terminal buffering (to allow reading input without pressing Enter).

Rendering: The game uses Unicode characters (🟦, 🟨, 🟪, 🟩, 🟥, 🟧, ⬜) to represent Tetrominoes in colored blocks.

The game board is displayed with walls represented by | and horizontal lines using --.

Game Over: The game ends when the board is full, and a new Tetromino cannot be placed at the top. A "Game Over!" message is displayed, and the player can choose to restart or exit.

Example Screenshot: The game renders a simple game board in the terminal, with colored Tetrominoes falling from the top:

mathematica

| |
| 🟦 |
| 🟦🟦 |
| 🟦🟦 |

🟦🟦
[ A ] Left [ D ] Right [ S ] Down [ W ] Rotate [Space] Hard Drop [ P ] Pause [ R ] Restart [ X ] Exit
In this example, the 🟦 Tetromino is falling, and the controls are displayed at the bottom.
License: This project is open-source and available for modification and distribution. You are free to use, modify, and contribute to this code.

Contributions: Feel free to fork this repository, create issues, submit pull requests, or suggest improvements. Contributions are welcome!
