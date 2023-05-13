#pragma once

#include "../board/chess_piece.h"
#include "bishop.h"
#include "rook.h"

class queen : public bishop, public rook {
    protected:
	auto valid_move(unsigned int to_x, unsigned int to_y) -> int override;
	auto print() -> char override;

    public:
	queen(const queen &) = default;
	queen(queen &&) = delete;
	auto operator=(const queen &) -> queen & = default;
	auto operator=(queen &&) -> queen & = delete;
	queen(unsigned int x_, unsigned int y_, bool isWhite, string name_,
	    chess_board *board_);
	~queen() override;
};
