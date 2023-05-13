#include "pawn.h"

#include <cmath>
#include <memory>

#define LIMIT 6

pawn::~pawn() = default;

auto
pawn::valid_move(unsigned int to_x, unsigned int to_y) -> int
{
	shared_ptr<chess_piece> cp =
	    this->get_chessboard()->get_board().get(to_x, to_y);

	if (this->get_x() == to_x) {
		if (cp) {
			return 0;
		}

		if ((this->get_is_white() && this->get_y() > to_y) ||
		    (!this->get_is_white() && this->get_y() < to_y)) {
			return 0;
		}

		if ((this->get_is_white() && to_y == this->get_y() + 1) ||
		    (!this->get_is_white() && to_y == this->get_y() - 1)) {
			return 1;
		}

		if ((this->get_is_white() && (this->get_y() == 1) &&
			(to_y == this->get_y() + 2) &&
			(this->get_chessboard()->get_board().get(to_x,
			     to_y - 1) == nullptr)) ||
		    (!this->get_is_white() && (this->get_y() == LIMIT) &&
			(to_y == this->get_y() - 2) &&
			(this->get_chessboard()->get_board().get(to_x,
			     to_y + 1) == nullptr))) {
			return 1;
		}
	} else if (std::abs(static_cast<int>(this->get_y()) -
		       static_cast<int>(to_y)) == 1 &&
	    std::abs(static_cast<int>(this->get_x()) -
		static_cast<int>(to_x)) == 1) {
		if (cp != nullptr) {
			if (this->get_is_white() != cp->get_is_white()) {
				return 2;
			}
		}
	}
	return 0;
}

auto
pawn::print() -> char
{
	return this->get_is_white() ? 'P' : 'p';
}
