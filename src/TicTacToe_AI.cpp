//============================================================================
// Name        : TicTacToe Minimax
// Author      : tux76
// Description : Uses the Minimax algorithm to analyze and play a game of TicTacToe
//============================================================================
/*
 * When run on empty board:
	 * Original Processes: 549,945
	 * With AlphaBeta Pruning: 145,659
	 * With AlphaBeta and maximum value pruning: 99,845
 */


#include <iostream>
using namespace std;
#include <vector>
#include <unordered_map>
#include <string>


#define GS_ACTIVE 2
#define GS_DRAW 0
#define GS_POS_WIN 1
#define GS_NEG_WIN -1

#define SPACE_EMPTY 0
#define SPACE_X 1
#define SPACE_O -1


// GAME
// =================================
const int COMPARISONS[8][3] = {
		{0,1,2},
		{3,4,5},
		{6,7,8},
		{0,3,6},
		{1,4,7},
		{2,5,8},
		{0,4,8},
		{2,4,6}
};

class Game {
private:
	vector<int> possiblePlays;

	void calculateTurn() {
		int x = 0;
		int o = 0;
		for (int space : board) {
			if (space == 1) x++;
			else if (space == -1) o++;
		}
		if (x == o) {
			turn = 1;
		} else {
			turn = -1;
		}
	}
public:
	int board[9];
	int turn;
	vector<int> moveHistory;

	Game(int _board[9], int _turn = 0) {
		for (int i = 0; i<9; i++) {
			board[i] = _board[i];
		}
		if (_turn != 0) turn = _turn;
		else calculateTurn();
	}

	int getState() const {
		int state = GS_DRAW;
		// Check for draw
		for (int i = 0; i < 9 && state == GS_DRAW; i++) {
			if (board[i] == SPACE_EMPTY) state = GS_ACTIVE;
		}
		// Check for 3 in a row
		for (int ci = 0; ci<8 && state == GS_ACTIVE; ci++) {
			int a = board[COMPARISONS[ci][0]]; int b = board[COMPARISONS[ci][1]]; int c = board[COMPARISONS[ci][2]];
			if (a == b && b == c && a != 0) {
				state = a;
			}
		}
		return state;
	}
	vector<int> getPossiblePlays() {
		possiblePlays.clear();
		for (int i = 0; i < 9; i++) {
			if (board[i] == 0) possiblePlays.push_back(i);
		}
		return possiblePlays;
	}
	void play(int space) {
		board[space] = turn;
		turn *= -1;
		moveHistory.push_back(space);
	}
	void undoPlay() {
		int lastMove = moveHistory.back();
		moveHistory.pop_back();
		board[lastMove] = SPACE_EMPTY;
		turn *= -1;
	}
};


// INTERFACE
// =================================
const unordered_map<int, char> CHAR_LOOKUP_TABLE {
	{0, '-'},
	{1, 'x'},
	{-1, 'o'}
};

void printGame(const Game &game, bool oneLine = 0) {
	for (int i = 0; i<9; i++) {
		cout << CHAR_LOOKUP_TABLE.at(game.board[i]) << " ";
		if (i % 3 == 2 && !oneLine) {
			cout << endl;
		}
	}
	cout << '(' << game.getState() << ") " << "Next: " << CHAR_LOOKUP_TABLE.at(game.turn) << endl;
}


// MINIMAX
// =================================
int nodesProcessed;
float minimax(Game &game, float alpha = -2, float beta = 2) {
	nodesProcessed++;
	// Check if leaf node
	int gameState = game.getState();
	if (gameState != GS_ACTIVE) {
		return gameState;
	}

	float bestValue;
	if (game.turn == 1) { // MAXIMIZER
		bestValue = -1;
		float childValue;
		for (int& play : game.getPossiblePlays()) {
			game.play(play);

			childValue = minimax(game, alpha, beta);
			if (childValue > bestValue) bestValue = childValue;
			if (childValue > alpha) alpha = childValue;

			game.undoPlay();
			if (alpha > beta) break;
			if (bestValue == 1) break;
		}
	}
	else { // MINIMIZER
		bestValue = 1;
		float childValue;
		for (int& play : game.getPossiblePlays()) {
			game.play(play);

			childValue = minimax(game, alpha, beta);
			if (childValue < bestValue) bestValue = childValue;
			if (childValue < beta) beta = childValue;

			game.undoPlay();
			if (beta < alpha) break;
			if (bestValue == -1) break;
		}
	}
	return bestValue;
}

int selectPlay(Game game) {
	int player = game.turn;
	int bestPlay;
	float bestValue = game.turn*-1;
	float value;
	for (int& move : game.getPossiblePlays()) {
		game.play(move);

		value = minimax(game);
		if ((value > bestValue && player == 1) or (value < bestValue && player == -1)) {
			bestValue = value;
			bestPlay = move;
		}

		game.undoPlay();
	}
	return bestPlay;
}


// MAIN
// =================================
int main() {
	int board[9] = { 0, 0, 0,
				     0, 0, 0,
					 0, 0, 0};

	Game originGame(board);

//	cout << minimax(originGame) << endl << nodesProcessed << endl;

	string input;
	int play;
	int gameState;
	while (true) {
		gameState = originGame.getState();

		printGame(originGame);
		cout << "Enter a move (type 'exit' to quit): ";
		getline(cin, input);

		if (input == "exit") break;
		else if (input == "-") {
			originGame.undoPlay();
			continue;
		}
		else if (input == "r") {
			for (int i = 0; i < 9; i++) {
				originGame.board[i] = SPACE_EMPTY;
			}
			originGame.moveHistory.clear();
			originGame.turn = 1;
			cout << endl;
			continue;
		}
		else if (gameState == GS_ACTIVE) {
			if (input == "a1") play = 0;
			else if (input == "a2") play = 1;
			else if (input == "a3") play = 2;
			else if (input == "b1") play = 3;
			else if (input == "b2") play = 4;
			else if (input == "b3") play = 5;
			else if (input == "c1") play = 6;
			else if (input == "c2") play = 7;
			else if (input == "c3") play = 8;
			else if (input == "" && gameState == GS_ACTIVE) {
				cout << "AI SELECTION" << endl;
				nodesProcessed = 0;
				play = selectPlay(originGame);
				cout << "Processed: " << nodesProcessed << endl;
			}
			else {
				cout << "Please try again." << endl << endl;
				continue;
			}
		}
		else {
			cout << "Invalid input. This game is no longer active." << endl << endl;
			continue;
		}


		if (gameState == GS_ACTIVE) originGame.play(play);

		cout << endl;
	}

	printGame(originGame);

	cout << "Finished" << endl;
	return 0;
}
