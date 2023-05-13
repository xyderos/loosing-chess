#include <unistd.h>

#include "../src/board/chess_board.h"
#include "../src/board/chess_move.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::stringstream;

static auto
play(const string &color, const string &ai) -> int
{
	chess_board chess;
	stringstream s;
	s << "RNBKQBNR" << endl;
	s << "PPPPPPPP" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "pppppppp" << endl;
	s << "rnbqkbnr" << endl;

	s >> chess;

	if (color == "white" && ai == "naive") {
		int counter = 0;
		for (;;) {
			cout << "------------ROUND: " << counter + 1
			     << "-------------" << endl;
			chess.naive(true);
			chess.print();
			if (!chess.game_over(false)) {
				cout << "White won\n" << endl;
				return -1;
			}

			chess.smart(false);
			chess.print();
			if (!chess.game_over(true)) {
				cout << "Black won\n" << endl;
				return -1;
			}
			counter++;
		}
	} else if (color == "white" && ai == "smart") {
		int counter = 0;
		for (;;) {
			cout << "------------ROUND: " << counter + 1
			     << "-------------" << endl;
			chess.smart(true);
			chess.print();
			if (!chess.game_over(false)) {
				cout << "White won\n" << endl;
				return -1;
			}
			chess.naive(false);
			chess.print();
			if (!chess.game_over(true)) {
				cout << "Black won\n" << endl;
				return -1;
			}
			counter++;
		}
	} else if (color == "black" && ai == "naive") {
		int counter = 0;
		for (;;) {
			cout << "------------ROUND: " << counter + 1
			     << "-------------" << endl;
			chess.smart(true);
			chess.print();
			if (!chess.game_over(false)) {
				cout << "White won\n" << endl;
				return -1;
			}
			chess.naive(false);
			chess.print();
			if (!chess.game_over(true)) {
				cout << "Black won\n" << endl;
				return -1;
			}
			counter++;
		}
	} else {
		int counter = 0;
		for (;;) {
			cout << "------------ROUND: " << counter + 1
			     << "-------------" << endl;
			chess.naive(true);
			chess.print();
			if (!chess.game_over(false)) {
				cout << "White won\n" << endl;
				return -1;
			}
			chess.smart(false);
			chess.print();
			if (!chess.game_over(true)) {
				cout << "Black won\n" << endl;
				return -1;
			}
			counter++;
		}
	}
}

auto
main(int argc, char *argv[]) -> int
{
	if (argc != 3) {
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}
	string color = argv[1];
	string ai = argv[2];
	play(color, ai);

	return 0;
}
