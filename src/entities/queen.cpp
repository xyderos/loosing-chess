#include "../board/chess_board.h"
#include "bishop.h"
#include "queen.h"

#include <utility>

queen::queen(unsigned int x_, unsigned int y_, bool isWhite, string name_,
    chess_board *board_)
    : chess_piece(x_, y_, isWhite, std::move(name_), board_)
    , bishop(x_, y_, isWhite, name_, board_)
    , rook(x_, y_, isWhite, name_, board_)
{
}

queen::~queen() = default;

auto
queen::valid_move(unsigned int to_x, unsigned int to_y) -> int
{
	int bishop = bishop::valid_move(to_x, to_y);
	int rook = rook::valid_move(to_x, to_y);
	return (bishop <= rook) ? rook : bishop;
}

auto
queen::print() -> char
{
	return this->bishop::get_is_white() ? 'Q' : 'q';
}
