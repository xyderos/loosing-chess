#include "knight.h"

#include <cmath>
#include <memory>

#define LIMIT 5.0

using namespace std;

knight::~knight() = default;

auto
knight::valid_move(unsigned int to_x, unsigned int to_y) -> int
{
	shared_ptr<chess_piece> cp =
	    this->get_chessboard()->get_board().get(to_x, to_y);
	unsigned int dx = (to_x > this->get_x() ? to_x - this->get_x() :
						  this->get_x() - to_x);
	unsigned int dy = (to_y > this->get_y() ? to_y - this->get_y() :
						  this->get_y() - to_y);

	// check if "go-to" square contains friendly piece
	if (cp && cp->get_is_white() == this->get_is_white()) {
		return 0;
	}

	if ((pow(dx, 2) + pow(dy, 2)) != LIMIT) {
		return 0;
	}

	return (cp == nullptr) ? 1 : 2;
}

auto
knight::print() -> char
{
	return this->get_is_white() ? 'N' : 'n';
}
