#pragma once

#include "../board/chess_board.h"

class chess_piece {

	friend void chess_board::move_piece(const chess_move &chessMove);

	unsigned int x, y;
	bool is_white;
	string name;
	chess_board *board;

    public:
	chess_piece(const chess_piece &) = default;
	chess_piece(chess_piece &&) = delete;
	auto operator=(const chess_piece &) -> chess_piece & = default;
	auto operator=(chess_piece &&) -> chess_piece & = delete;
	chess_piece(unsigned int, unsigned int, bool, string, chess_board *);

	virtual ~chess_piece();

	auto capturing_move(unsigned int, unsigned int) -> bool;
	auto non_capturing_move(unsigned int, unsigned int) -> bool;

	virtual auto get_capturing_moves() -> vector<chess_move>;
	virtual auto get_non_capturing_moves() -> vector<chess_move>;

	[[nodiscard]] auto get_is_white() const -> bool;
	void set_is_white(bool);
	[[nodiscard]] auto get_x() const -> unsigned int;
	void set_x(unsigned int);
	[[nodiscard]] auto get_y() const -> unsigned int;
	void set_y(unsigned int);
	[[nodiscard]] auto get_name() const -> string;
	void set_name(string);
	[[nodiscard]] auto get_chessboard() const -> chess_board *;
	void set_chessboard(chess_board *);
	virtual auto valid_move(unsigned int to_x, unsigned int to_y)
	    -> int = 0;
	virtual auto print() -> char = 0;
};
