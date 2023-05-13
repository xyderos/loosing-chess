#include "rook.h"

#include <cmath>
#include <memory>

using namespace std;

rook::~rook() = default;

auto
rook::valid_move(unsigned int to_x, unsigned int to_y) -> int
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

	if ((this->get_x() != to_x) && (this->get_y() != to_y)) {
		return 0;
	}

	if (dx == 0) {
		for (unsigned int i = 1; i < dy; i++) {
			if (this->get_y() < to_y) {
				if (this->get_chessboard()->get_board().get(
					this->get_x(), this->get_y() + i) !=
				    nullptr) {
					return 0;
				}
			} else if (this->get_y() > to_y) {
				if (this->get_chessboard()->get_board().get(
					this->get_x(), this->get_y() - i) !=
				    nullptr) {
					return 0;
				}
			}
		}
	} else if (dy == 0) {
		for (unsigned int i = 1; i < dx; i++) {
			if (this->get_x() < to_x) {
				if (this->get_chessboard()->get_board().get(
					this->get_x() + i, this->get_y()) !=
				    nullptr) {
					return 0;
				}
			} else if (this->get_x() > to_x) {
				if (this->get_chessboard()->get_board().get(
					this->get_x() - i, this->get_y()) !=
				    nullptr) {
					return 0;
				}
			}
		}
	}

	return (cp == nullptr) ? 1 : 2;
}

auto
rook::print() -> char
{
	return this->get_is_white() ? 'R' : 'r';
}
