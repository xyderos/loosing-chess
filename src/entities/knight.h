#pragma once

#include "../board/chess_piece.h"

class knight : virtual public chess_piece {
    protected:
	auto valid_move(unsigned int to_x, unsigned int to_y) -> int override;
	auto print() -> char override;

    public:
	knight(const knight &) = default;
	knight(knight &&) = delete;
	auto operator=(const knight &) -> knight & = default;
	auto operator=(knight &&) -> knight & = delete;
	using chess_piece::chess_piece;
	~knight() override;
};
