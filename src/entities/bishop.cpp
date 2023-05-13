#include "../board/chess_board.h"
#include "bishop.h"

#include <cmath>
#include <memory>

bishop::~bishop() = default;

auto
bishop::valid_move(unsigned int to_x, unsigned int to_y) -> int
{
	shared_ptr<chess_piece> cp =
	    this->get_chessboard()->get_board().get(to_x, to_y);
	unsigned int dx = (to_x > this->get_x() ? to_x - this->get_x() :
						  this->get_x() - to_x);
	unsigned int dy = (to_y > this->get_y() ? to_y - this->get_y() :
						  this->get_y() - to_y);

	if (cp != nullptr && cp->get_is_white() == this->get_is_white()) {
		return 0;
	}

	if (dx == dy) {
		for (unsigned int i = 1; i < dx; i++) {
			if (this->get_x() < to_x && this->get_y() < to_y) {
				if (this->get_chessboard()->get_board().get(
					this->get_x() + i, this->get_y() + i) !=
				    nullptr) {
					return 0;
				}
			} else if (this->get_x() < to_x &&
			    this->get_y() > to_y) {
				if (this->get_chessboard()->get_board().get(
					this->get_x() + i, this->get_y() - i) !=
				    nullptr) {
					return 0;
				}
			} else if (this->get_x() > to_x &&
			    this->get_y() < to_y) {
				if (this->get_chessboard()->get_board().get(
					this->get_x() - i, this->get_y() + i) !=
				    nullptr) {
					return 0;
				}
			} else if (this->get_x() > to_x &&
			    this->get_y() > to_y) {
				if (this->get_chessboard()->get_board().get(
					this->get_x() - i, this->get_y() - i) !=
				    nullptr) {
					return 0;
				}
			}
		}
	} else {
		return 0;
	}

	return (cp == nullptr) ? 1 : 2;
}

auto
bishop::print() -> char
{
	return this->get_is_white() ? 'B' : 'b';
}
