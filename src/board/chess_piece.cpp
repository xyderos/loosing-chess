#include "../board/chess_board.h"
#include "../entities/bishop.h"
#include "chess_move.h"
#include "chess_piece.h"

#include <memory>
#include <utility>
#include <vector>

#define LIMIT 8

using namespace std;

chess_piece::chess_piece(unsigned int x_, unsigned int y_, bool isWhite,
    string name_, chess_board *board_)
    : x(x_)
    , y(y_)
    , is_white(isWhite)
    , name(std::move(name_))
    , board(board_)
{
}

chess_piece::~chess_piece() = default;

auto
chess_piece::capturing_move(unsigned int to_x, unsigned int to_y) -> bool
{
	return (this->valid_move(to_x, to_y) == 2) ? true : false;
}

auto
chess_piece::non_capturing_move(unsigned int to_x, unsigned int to_y) -> bool
{
	return (this->valid_move(to_x, to_y) == 1) ? true : false;
}

auto
chess_piece::get_capturing_moves() -> vector<chess_move>
{
	vector<chess_move> cm;
	for (unsigned int x_ = 0; x_ < LIMIT; x_++) {
		for (unsigned int y_ = 0; y_ < LIMIT; y_++) {
			if (this->capturing_move(x_, y_)) {

				chess_move move = { this->x, this->y, x_, y_,
					this->board->get_board().get(this->x,
					    this->y) };
				cm.push_back(move);
			}
		}
	}
	return cm;
}

auto
chess_piece::get_non_capturing_moves() -> vector<chess_move>
{
	vector<chess_move> cm;
	for (unsigned int x_ = 0; x_ < LIMIT; x_++) {
		for (unsigned int y_ = 0; y_ < LIMIT; y_++) {
			if (this->non_capturing_move(x_, y_)) {
				chess_move move = { this->x, this->y, x_, y_,
					this->board->get_board().get(this->x,
					    this->y) };
				cm.push_back(move);
			}
		}
	}
	return cm;
}

auto
chess_piece::get_is_white() const -> bool
{
	return is_white;
}

void
chess_piece::set_is_white(bool w)
{
	this->is_white = w;
}

auto
chess_piece::get_x() const -> unsigned int
{
	return x;
}

void
chess_piece::set_x(unsigned int x_)
{
	this->x = x_;
}

auto
chess_piece::get_y() const -> unsigned int
{
	return y;
}

void
chess_piece::set_y(unsigned int y_)
{
	this->y = y_;
}

auto
chess_piece::get_name() const -> string
{
	return name;
}

void
chess_piece::set_name(string name_)
{
	this->name = std::move(name_);
}

auto
chess_piece::get_chessboard() const -> chess_board *
{
	return board;
}

void
chess_piece::set_chessboard(chess_board *b)
{
	this->board = b;
}
