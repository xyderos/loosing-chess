#pragma once

#include "../board/chess_piece.h"

class bishop : virtual public chess_piece {
    protected:
	auto valid_move(unsigned int to_x, unsigned int to_y) -> int override;
	auto print() -> char override;

    public:
	bishop(const bishop &) = default;
	bishop(bishop &&) = delete;
	auto operator=(const bishop &) -> bishop & = default;
	auto operator=(bishop &&) -> bishop & = delete;
	using chess_piece::chess_piece;
	~bishop() override;
};
