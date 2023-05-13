#pragma once

#include "../board/chess_piece.h"

class king : virtual public chess_piece {
    protected:
	auto valid_move(unsigned int to_x, unsigned int to_y) -> int override;
	auto print() -> char override;

    public:
	king(const king &) = default;
	king(king &&) = delete;
	auto operator=(const king &) -> king & = default;
	auto operator=(king &&) -> king & = delete;
	using chess_piece::chess_piece;
	~king() override;
};
