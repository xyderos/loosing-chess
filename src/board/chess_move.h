#pragma once

#include "chess_piece.h"

#include <memory>

struct chess_move {
	unsigned int from_x {}, from_y {}, to_x {}, to_y {};

	std::shared_ptr<chess_piece> piece;
};
