#include "../board/chess_board.h"
#include "../board/chess_move.h"
#include "king.h"

#include <cmath>
#include <memory>

using namespace std;

king::~king() = default;

auto
king::valid_move(unsigned int to_x, unsigned int to_y) -> int
{
	shared_ptr<chess_piece> cp =
	    this->get_chessboard()->get_board().get(to_x, to_y);
	unsigned int dx = (to_x > this->get_x() ? to_x - this->get_x() :
						  this->get_x() - to_x);
	unsigned int dy = (to_y > this->get_y() ? to_y - this->get_y() :
						  this->get_y() - to_y);

	if (cp && cp->get_is_white() == this->get_is_white()) {
		return 0;
	}

	if ((dx + dy != 1) && (dx * dy != 1)) {
		return 0;
	} else if (!cp) {
		return 1;
	} else {
		return 2;
	}
}

auto
king::print() -> char
{
	return this->get_is_white() ? 'K' : 'k';
}
