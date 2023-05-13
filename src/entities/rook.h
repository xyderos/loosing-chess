#pragma once

#include "../board/chess_piece.h"

class rook : virtual public chess_piece {
    protected:
	auto valid_move(unsigned int to_x, unsigned int to_y) -> int override;
	auto print() -> char override;

    public:
	rook(const rook &) = default;
	rook(rook &&) = delete;
	auto operator=(const rook &) -> rook & = default;
	auto operator=(rook &&) -> rook & = delete;
	using chess_piece::chess_piece;
	~rook() override;
};
