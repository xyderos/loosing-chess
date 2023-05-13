#pragma once

#include "../board/chess_piece.h"

class pawn : virtual public chess_piece {
    protected:
	auto valid_move(unsigned int to_x, unsigned int to_y) -> int override;
	auto print() -> char override;

    public:
	pawn(const pawn &) = default;
	pawn(pawn &&) = delete;
	auto operator=(const pawn &) -> pawn & = default;
	auto operator=(pawn &&) -> pawn & = delete;
	using chess_piece::chess_piece;
	~pawn() override;
};
