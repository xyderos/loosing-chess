#pragma once

#include "../matrix/matrix.h"

#include <iostream>
#include <memory>
#include <vector>

struct chess_move;
class chess_piece;

using std::istream;
using std::shared_ptr;
using std::string;
using std::vector;

class chess_board {
    private:
	matrix<shared_ptr<chess_piece>> chessboard;

    public:
	void initialize_board(matrix<shared_ptr<chess_piece>>);
	void move_piece(const chess_move &chessMove);
	void print();
	void naive(bool isWhite);
	void smart(bool isWhite);
	void undo_move(const chess_move &move, shared_ptr<chess_piece> cp);
	void print_info(const chess_move &move, bool isWhite);
	auto enemy_can_capture(const chess_move &move, bool isWhite) -> bool;
	auto game_over(bool isWhite) -> bool;

	auto get_board() -> matrix<shared_ptr<chess_piece>>;

	auto get_capturing_moves(bool isWhite) -> vector<chess_move>;
	auto get_non_capturing_moves(bool isWhite) -> vector<chess_move>;

	auto make_piece(unsigned int x, unsigned int y, bool isWhite,
	    string name, chess_board *board) -> shared_ptr<chess_piece>;
	auto promotion(unsigned int x, unsigned int y, bool isWhite,
	    const string &name, chess_board *board) -> shared_ptr<chess_piece>;
	auto not_random_promotion(unsigned int x, unsigned int y, bool isWhite,
	    const string &name, chess_board *board, unsigned int i)
	    -> shared_ptr<chess_piece>;
};

auto operator>>(istream &, chess_board &) -> chess_board &;
auto random_int(unsigned long num) -> unsigned int;
