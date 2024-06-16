# Tic-Tac-Toe AI
C++ Artificial Intelligence Program for Playing Tic-Tac-Toe Using the Minimax Algorithm

## Program overview
This algorithm searches all possible outcomes of any Tic-Tac-Toe board and selects the best possible move for the current player. Because the game is so small, all possible outcomes can be computed in a very short amount of time.

The user interface runs in the terminal. It is more focused on exploring the capabilities of the _Minimax_ algorithm rather than providing a clean and smooth user interface, although I plan to make a user-friendly program to play multiple turn-based games like this in the future.

## Install (Linux & MacOS)
To install on Linux or MacOS:
1. Be sure you have the `g++` compiler and that it supports C++11 or later. The `make` and `git` packages are also required.
2. Clone the repository. `git clone https://github.com/tux-76/TicTacToe-AI`
3. Make the file from the release directory. `make -C Release all`
4. Run the executable. `./Release/TicTacToe_AI`

**NOTE:** If you are on _Windows_ or this method doesn't work for you, try copying the `TicTacToe_AI.cpp` file and running it with your own compiler, ignoring the makefile.

## Controls
Before each move you will be presented with the current 3x3 Tic-Tac-Toe board, with blank spaces being represented by a `-`, like so:

```
x - -
- 0 -
- - x
Next: x
```

You may enter a move by combining the row, denoted by an `A`, `B`, or `C`, and the column `1`, `2`, `3` and press `Enter`. (Eg. Top left: `A1`, bottom right: `C3`) Like this:
```
  1 2 3
A - - -
B - - -
C - - -
```

The AI can play for both X and O (so can the user). **Press Enter _without_ entering a move for an AI selection.**
So if the user wants to play **O** against the AI as **X**, he will press `Enter` without a move every time it is **X**'s turn, and enter a move every time it is **O**'s turn.

## The algorithm behind the AI
The AI in this program is built around the **Minimax** algorithm. Minimax is a type of algorithm that allows computers to determine the best possible move for any state of a turn-based game. It essentially scans the possible outcomes of any _game state_ and determines which outcome is most desirable and achievable, given that the other player is also playing optimally. For any _game state_ (the arrangement of pieces on the board), the computer first gets the possible plays of the next player. After it gets the likelyhood that Player 1 will win—known as the _state value_—for each of the child _game states_ (either by computing that the game is over or by running the Minimax algorithm recursively), it then selects either the _minimum_ or the _maximum_ of all those values based on who's turn it is (Player 1 wants the outcome with the _greatest_ value, wheras his opponent, Player 2, wants the most _negative_ value). Thus, for any game state, the _Minimax_ algorithm determines the likelyhood that Player1 will win given both players play optimally. Selecting the best move, then, is as simple as running _Minimax_ for each possible move and returning the most desirable one.
