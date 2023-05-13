#include "../entities/bishop.h"
#include "../entities/king.h"
#include "../entities/knight.h"
#include "../entities/pawn.h"
#include "../entities/queen.h"
#include "../entities/rook.h"
#include "chess_board.h"
#include "chess_move.h"

#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <random>
#include <utility>
#include <vector>

#define LIMIT 8

using namespace std;

auto
chess_board::get_board() -> matrix<shared_ptr<chess_piece>>
{
	return this->chessboard;
}

void
chess_board::initialize_board(matrix<shared_ptr<chess_piece>> m)
{
	chessboard = std::move(m);
}

void
chess_board::move_piece(const chess_move &move)
{
	move.piece->x = move.to_x;
	move.piece->y = move.to_y;

	this->chessboard.set(0, move.to_x + LIMIT * move.to_y, move.piece);

	this->chessboard.set(0, move.from_x + LIMIT * move.from_y, nullptr);
}

auto
chess_board::get_capturing_moves(bool isWhite) -> vector<chess_move>
{
	vector<chess_move> cm;
	for (unsigned int x = 0; x < LIMIT; x++) {
		for (unsigned int y = 0; y < LIMIT; y++) {
			shared_ptr<chess_piece> cp = this->chessboard.get(x, y);
			if (cp != nullptr && cp->get_is_white() == isWhite) {
				for (const auto &i :
				    cp->get_capturing_moves()) {
					cm.push_back(i);
				}
			}
		}
	}
	return cm;
}

auto
chess_board::get_non_capturing_moves(bool isWhite) -> vector<chess_move>
{
	vector<chess_move> cm;
	for (unsigned int y = 0; y < LIMIT; y++) {
		for (unsigned int x = 0; x < LIMIT; x++) {
			shared_ptr<chess_piece> cp = this->chessboard.get(x, y);

			if (cp != nullptr && cp->get_is_white() == isWhite) {
				for (const auto &i :
				    cp->get_non_capturing_moves()) {
					cm.push_back(i);
				}
			}
		}
	}

	return cm;
}

auto
chess_board::promotion(unsigned int x, unsigned int y, bool isWhite,
    const string &name, chess_board *board) -> shared_ptr<chess_piece>
{
	std::array<string, 4> names = { "bishop", "knight", "queen", "rook" };
	auto rand_index = random_int(4);
	string rand_name = names.at(rand_index);

	if ((name == "pawn" && isWhite && y == LIMIT - 1) ||
	    (name == "pawn" && !isWhite && y == 0)) {
		shared_ptr<chess_piece> cp = make_piece(x, y, isWhite,
		    rand_name, board);
		return cp;
	} else {
		return nullptr;
	}
}

auto
chess_board::not_random_promotion(unsigned int x, unsigned int y, bool isWhite,
    const string &name, chess_board *board, unsigned int i)
    -> shared_ptr<chess_piece>
{
	std::array<string, 4> names = { "bishop", "knight", "queen", "rook" };
	auto rand_index = random_int(4);
	string rand_name = names.at(rand_index);

	if ((name == "pawn" && isWhite && y == LIMIT - 1) ||
	    (name == "pawn" && !isWhite && y == 0)) {
		shared_ptr<chess_piece> cp = make_piece(x, y, isWhite,
		    names.at(i), board);
		return cp;
	} else {
		return nullptr;
	}
}

auto
chess_board::make_piece(unsigned int x, unsigned int y, bool isWhite,
    string name, chess_board *board) -> shared_ptr<chess_piece>
{
	shared_ptr<chess_piece> cp;
	if (name == "bishop") {
		cp = make_shared<bishop>(x, y, isWhite, name, board);
	} else if (name == "knight") {
		cp = make_shared<knight>(x, y, isWhite, name, board);
	} else if (name == "rook") {
		cp = make_shared<rook>(x, y, isWhite, name, board);
	} else {
		cp = make_shared<queen>(x, y, isWhite, name, board);
	}
	return cp;
}

void
chess_board::naive(bool isWhite)
{
	vector<chess_move> cap_moves = get_capturing_moves(isWhite);
	vector<chess_move> non_cap_moves = get_non_capturing_moves(isWhite);
	chess_move move {};

	if (cap_moves.size() > 0) {
		auto x = random_int(cap_moves.size());
		move = cap_moves.at(x);
		move_piece(move);
	} else if (non_cap_moves.size() > 0) {
		auto x = random_int(non_cap_moves.size());
		move = non_cap_moves.at(x);
		move_piece(move);
	} else {
		cout << "no moves" << endl;
	}

	print_info(move, isWhite);

	if (move.piece != nullptr) {
		shared_ptr<chess_piece> cp = promotion(move.to_x, move.to_y,
		    move.piece->get_is_white(), move.piece->get_name(),
		    move.piece->get_chessboard());
		if (cp != nullptr) {
			this->chessboard.set(0, move.to_x + LIMIT * move.to_y,
			    cp);
		}
	}
}

void
chess_board::undo_move(const chess_move &move,
    shared_ptr<chess_piece> cp_deleted)
{
	move.piece->set_x(move.from_x);
	move.piece->set_y(move.from_y);

	this->chessboard.set(0, move.from_x + LIMIT * move.from_y, move.piece);
	this->chessboard.set(0, move.to_x + LIMIT * move.to_y,
	    std::move(cp_deleted));
}

auto
chess_board::enemy_can_capture(const chess_move &move, bool isWhite) -> bool
{
	auto x = move.to_x, y = move.to_y;
	shared_ptr<chess_piece> cp;

	for (unsigned int i = 0; i < LIMIT; i++) {
		for (unsigned int z = 0; z < LIMIT; z++) {
			cp = this->chessboard.get(i, z);
			if (cp != nullptr && cp->get_is_white() != isWhite &&
			    cp->valid_move(x, y) == 2) {
				return true;
			}
		}
	}
	return false;
}

void
chess_board::smart(bool isWhite)
{
	vector<chess_move> cap_moves = get_capturing_moves(isWhite);
	vector<chess_move> cap_moves_enemy = get_capturing_moves(!isWhite);
	vector<chess_move> non_cap_moves = get_non_capturing_moves(isWhite);

	chess_move move {};
	shared_ptr<chess_piece> cp;
	bool noCap = true;
	bool isPromoted = false;

	if (cap_moves.size() > 0) {
		for (const auto &i : cap_moves) {
			cp = this->chessboard.get(i.to_x, i.to_y);
			move_piece(i);
			if (enemy_can_capture(i, isWhite)) {
				noCap = false;
				print_info(i, isWhite);
				break;
			} else {
				undo_move(i, cp);
			}
		}

		if (noCap) {
			auto x = random_int(cap_moves.size());
			move = cap_moves.at(x);
			move_piece(move);
			print_info(move, isWhite);
		}
	} else if (non_cap_moves.size() > 0) {
		for (const auto &i : non_cap_moves) {
			cp = this->chessboard.get(i.to_x, i.to_y);
			move_piece(i);
			if (enemy_can_capture(i, isWhite)) {
				noCap = false;
				print_info(i, isWhite);
				break;
			} else {
				undo_move(i, cp);
			}
		}

		if (noCap) {
			auto x = random_int(non_cap_moves.size());
			move = non_cap_moves.at(x);
			move_piece(move);
			print_info(move, isWhite);
		}
	}

	if (move.piece != nullptr) {
		shared_ptr<chess_piece> cp_;
		vector<chess_move> cap_moves_after_promotion;
		for (unsigned int i = 0; i < 4; i++) {
			cp_ = not_random_promotion(move.to_x, move.to_y,
			    move.piece->get_is_white(), move.piece->get_name(),
			    move.piece->get_chessboard(), i);

			if (cp_ != nullptr) {
				this->chessboard.set(0,
				    move.to_x + LIMIT * move.to_y, cp_);
			}

			cap_moves_after_promotion = get_capturing_moves(
			    isWhite);
			if (cap_moves_after_promotion.size() <=
			    cap_moves.size()) {
				isPromoted = true;
				break;
			}
		}

		if (cp_ != nullptr && !isPromoted) {
			cp_ = promotion(move.to_x, move.to_y,
			    move.piece->get_is_white(), move.piece->get_name(),
			    move.piece->get_chessboard());
			this->chessboard.set(0, move.to_x + LIMIT * move.to_y,
			    cp_);
		}
	}
}

void
chess_board::print_info(const chess_move &move, bool isWhite)
{
	unsigned int from_x = move.from_x, from_y = move.from_y,
		     to_x = move.to_x, to_y = move.to_y;

	cout << "\n";

	if (isWhite) {
		cout << "Player: White" << endl;
		cout << "Chesspiece: " << move.piece->print() << std::endl;
		cout << "From position: (" << from_x << "," << from_y << ")"
		     << endl;
		cout << "To position: (" << to_x << "," << to_y << ")" << endl;
	} else {
		cout << "Player: Black" << endl;
		cout << "Chesspiece: " << move.piece->print() << std::endl;
		cout << "From position: (" << from_x << "," << from_y << ")"
		     << endl;
		cout << "To position: (" << to_x << "," << to_y << ")" << endl;
	}
}

auto
chess_board::game_over(bool isWhite) -> bool
{
	bool king = false;
	shared_ptr<chess_piece> cp;

	for (unsigned int i = 0; i < LIMIT; i++) {
		for (unsigned int j = 0; j < LIMIT; j++) {
			cp = this->chessboard.get(i, j);
			if (cp != nullptr && cp->get_name() == "king" &&
			    cp->get_is_white() == isWhite) {
				king = true;
			}
		}
	}
	return king;
}

auto
operator>>(istream &is, chess_board &board) -> chess_board &
{
	matrix<shared_ptr<chess_piece>> m(LIMIT);
	int c = 0;
	unsigned int counter = 0;
	c = is.get();
	while (is) {
		if (c == '\n') {
			c = is.get();
		} else {
			auto x = counter % LIMIT;
			auto y = floor(counter / LIMIT);
			switch (c) {
			case 'K':
				m.set(0, counter,
				    make_shared<king>(x, y, true, "king",
					&board));
				break;
			case 'k':
				m.set(0, counter,
				    make_shared<king>(x, y, false, "king",
					&board));
				break;
			case 'Q':
				m.set(0, counter,
				    make_shared<queen>(x, y, true, "queen",
					&board));
				break;
			case 'q':
				m.set(0, counter,
				    make_shared<queen>(x, y, false, "queen",
					&board));
				break;
			case 'N':
				m.set(0, counter,
				    make_shared<knight>(x, y, true, "knight",
					&board));
				break;
			case 'n':
				m.set(0, counter,
				    make_shared<knight>(x, y, false, "knight",
					&board));
				break;
			case 'P':
				m.set(0, counter,
				    make_shared<pawn>(x, y, true, "pawn",
					&board));
				break;
			case 'p':
				m.set(0, counter,
				    make_shared<pawn>(x, y, false, "pawn",
					&board));
				break;
			case 'B':
				m.set(0, counter,
				    make_shared<bishop>(x, y, true, "bishop",
					&board));
				break;
			case 'b':
				m.set(0, counter,
				    make_shared<bishop>(x, y, false, "bishop",
					&board));
				break;
			case 'R':
				m.set(0, counter,
				    make_shared<rook>(x, y, true, "rook",
					&board));
				break;
			case 'r':
				m.set(0, counter,
				    make_shared<rook>(x, y, false, "rook",
					&board));
				break;
			default:
				m.set(0, counter, nullptr);
			}
			counter++;
			c = is.get();
		}
	}

	board.initialize_board(m);
	return board;
}

void
chess_board::print()
{
	unsigned int i = 0, j = 0;
	cout << " ---------------------------------\n";
	for (i = 0; i < LIMIT; ++i) {
		cout << " | ";
		for (j = 0; j < LIMIT; ++j) {
			if (!chessboard[i * LIMIT + j]) {
				cout << " "
				     << " | ";
			} else {
				cout << chessboard[i * LIMIT + j]->print()
				     << " | ";
			}
		}
		cout << "\n ---------------------------------\n";
	}
	cout << "\n";
}

auto
random_int(unsigned long limit) -> unsigned int
{
	srand(static_cast<unsigned>(time(nullptr)));
	unsigned x = static_cast<unsigned int>(rand()) % limit;
	return x;
}
