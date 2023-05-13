#include "../../src/board/chess_board.h"
#include "../../src/board/chess_move.h"
#include "../../src/board/chess_piece.h"
#include "test_chessboard.h"

using std::endl;
using std::shared_ptr;
using std::stringstream;
using std::vector;

void
test_chessboard::test_case_1()
{
	chess_board chess;
	std::stringstream s;

	s << "Q..n...r" << endl;
	s << "........" << endl;
	s << "n.r....." << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);
	shared_ptr<chess_piece> cp = chess.get_board().get(0, 0);
	vector<chess_move> ncm1 = chess.get_non_capturing_moves(true);
	vector<chess_move> ncm2 = chess.get_non_capturing_moves(false);
	int move1 = cp->valid_move(3, 1);
	int move2 = cp->valid_move(1, 0);
	int move3 = cp->valid_move(3, 0);

	unsigned long cm1_expected = 3, cm2_expected = 0, ncm1_expected = 4,
		      ncm2_expected = 30;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(move1, 0);
	CPPUNIT_ASSERT_EQUAL(move2, 1);
	CPPUNIT_ASSERT_EQUAL(move3, 2);
	CPPUNIT_ASSERT_EQUAL(ncm1.size(), ncm1_expected);
	CPPUNIT_ASSERT_EQUAL(ncm2.size(), ncm2_expected);
}

void
test_chessboard::test_case_2()
{
	chess_board chess;
	std::stringstream s;

	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << ".r......" << endl;
	s << ".p......" << endl;
	s << "...P...n" << endl;
	s << "......P." << endl;
	s << ".N...B.." << endl;
	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);
	shared_ptr<chess_piece> cp = chess.get_board().get(1, 7);
	int move1 = cp->valid_move(2, 5);
	int move2 = cp->valid_move(0, 5);
	int move3 = cp->valid_move(3, 6);

	unsigned long cm1_expected = 1, cm2_expected = 0;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(move1, 1);
	CPPUNIT_ASSERT_EQUAL(move2, 1);
	CPPUNIT_ASSERT_EQUAL(move3, 1);
}

void
test_chessboard::test_case_3()
{
	chess_board chess;
	std::stringstream s;

	s << "q......." << endl;
	s << "....p..." << endl;
	s << "....Q..." << endl;
	s << ".r......" << endl;
	s << ".p..B..." << endl;
	s << "...P...n" << endl;
	s << "......P." << endl;
	s << "RN...B.." << endl;
	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);
	shared_ptr<chess_piece> cp = chess.get_board().get(6, 6);
	shared_ptr<chess_piece> cp1 = chess.get_board().get(0, 7);
	shared_ptr<chess_piece> cp2 = chess.get_board().get(0, 0);

	int move1 = cp->valid_move(7, 5);
	int move2 = cp->valid_move(0, 0);
	int move3 = cp->valid_move(6, 5);
	int move4 = cp1->valid_move(7, 7);
	int move5 = cp1->valid_move(0, 6);
	int move6 = cp1->valid_move(0, 0);
	int move7 = cp2->valid_move(3, 2);
	int move8 = cp2->valid_move(1, 1);
	int move9 = cp2->valid_move(4, 4);

	unsigned long cm1_expected = 5, cm2_expected = 2;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(move1, 2);
	CPPUNIT_ASSERT_EQUAL(move2, 0);
	CPPUNIT_ASSERT_EQUAL(move3, 0);
	CPPUNIT_ASSERT_EQUAL(move4, 0);
	CPPUNIT_ASSERT_EQUAL(move5, 1);
	CPPUNIT_ASSERT_EQUAL(move6, 2);
	CPPUNIT_ASSERT_EQUAL(move7, 0);
	CPPUNIT_ASSERT_EQUAL(move8, 1);
	CPPUNIT_ASSERT_EQUAL(move9, 2);
}
void
test_chessboard::test_case_4()
{
	chess_board chess;
	std::stringstream s;

	s << "........" << endl;
	s << ".......p" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "Q.P..pp." << endl;
	s << ".....PPP" << endl;
	s << "......NR" << endl;
	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);
	shared_ptr<chess_piece> cp = chess.get_board().get(6, 7);

	int move1 = cp->valid_move(0, 0);
	int move2 = cp->valid_move(7, 5);
	int move3 = cp->valid_move(5, 5);

	unsigned long cm1_expected = 4, cm2_expected = 3;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(move1, 0);
	CPPUNIT_ASSERT_EQUAL(move2, 1);
	CPPUNIT_ASSERT_EQUAL(move3, 2);
}
void
test_chessboard::test_case_5()
{
	chess_board chess;
	std::stringstream s;

	s << "........" << endl;
	s << "......p." << endl;
	s << ".......R" << endl;
	s << "..npn..." << endl;
	s << "...P...." << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);
	vector<chess_move> ncm1 = chess.get_non_capturing_moves(true);
	vector<chess_move> ncm2 = chess.get_non_capturing_moves(false);

	unsigned long cm1_expected = 2, cm2_expected = 1, cm3_expected = 15,
		      cm4_expected = 18;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(ncm1.size(), cm3_expected);
	CPPUNIT_ASSERT_EQUAL(ncm2.size(), cm4_expected);
}
void
test_chessboard::test_case_6()
{
	chess_board chess;
	std::stringstream s;

	s << "RNBQKBNR" << endl;
	s << "PPPPPPPP" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "pppppppp" << endl;
	s << "rnbqkbnr" << endl;

	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);
	vector<chess_move> ncm1 = chess.get_non_capturing_moves(true);
	vector<chess_move> ncm2 = chess.get_non_capturing_moves(false);

	unsigned long cm1_expected = 0, cm2_expected = 0, cm3_expected = 20,
		      cm4_expected = 20;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(ncm1.size(), cm3_expected);
	CPPUNIT_ASSERT_EQUAL(ncm2.size(), cm4_expected);
}
void
test_chessboard::test_case_7()
{
	chess_board chess;
	std::stringstream s;

	s << "rnbqkbnr" << endl;
	s << "p.pppppp" << endl;
	s << "........" << endl;
	s << ".p......" << endl;
	s << "....P..." << endl;
	s << "........" << endl;
	s << "PPPP.PPP" << endl;
	s << "RNBQKBNR" << endl;

	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);

	shared_ptr<chess_piece> cp = chess.get_board().get(1, 0);

	int move1 = cp->valid_move(0, 0);
	int move2 = cp->valid_move(0, 2);
	int move3 = cp->valid_move(2, 2);
	unsigned long cm1_expected = 1, cm2_expected = 0;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(move1, 0);
	CPPUNIT_ASSERT_EQUAL(move2, 1);
	CPPUNIT_ASSERT_EQUAL(move3, 1);
}
void
test_chessboard::test_case_8()
{
	chess_board chess;
	std::stringstream s;

	s << "Kb......" << endl;
	s << "nn......" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;

	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);

	shared_ptr<chess_piece> cp = chess.get_board().get(0, 0);

	int move1 = cp->valid_move(7, 7);
	int move2 = cp->valid_move(1, 0);
	int move3 = cp->valid_move(1, 1);

	unsigned long cm1_expected = 3, cm2_expected = 0;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(move1, 0);
	CPPUNIT_ASSERT_EQUAL(move2, 2);
	CPPUNIT_ASSERT_EQUAL(move3, 2);
}
void
test_chessboard::test_case_9()
{

	chess_board chess;
	std::stringstream s;

	s << ".....Q.." << endl;
	s << "...q...." << endl;
	s << "......Q." << endl;
	s << "q......." << endl;
	s << ".......Q" << endl;
	s << ".q......" << endl;
	s << "....Q..." << endl;
	s << "..q....." << endl;

	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);

	shared_ptr<chess_piece> cp = chess.get_board().get(5, 0);

	int move1 = cp->valid_move(7, 7);
	int move2 = cp->valid_move(7, 0);
	int move3 = cp->valid_move(5, 1);

	unsigned long cm1_expected = 0, cm2_expected = 0;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(move1, 0);
	CPPUNIT_ASSERT_EQUAL(move2, 1);
	CPPUNIT_ASSERT_EQUAL(move3, 1);
}
void
test_chessboard::test_case_10()
{
	chess_board chess;
	std::stringstream s;
	s << "R..n...." << endl;
	s << "bn......" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;

	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);

	shared_ptr<chess_piece> cp = chess.get_board().get(0, 0);

	int move1 = cp->valid_move(7, 7);
	int move2 = cp->valid_move(1, 0);
	int move3 = cp->valid_move(3, 0);

	unsigned long cm1_expected = 2, cm2_expected = 0;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(move1, 0);
	CPPUNIT_ASSERT_EQUAL(move2, 1);
	CPPUNIT_ASSERT_EQUAL(move3, 2);
}
void
test_chessboard::test_case_11()
{
	chess_board chess;
	std::stringstream s;
	s << "B..n...." << endl;
	s << "bn......" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;

	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);

	shared_ptr<chess_piece> cp = chess.get_board().get(0, 0);

	int move1 = cp->valid_move(1, 0);
	int move2 = cp->valid_move(7, 7);
	int move3 = cp->valid_move(1, 1);

	unsigned long cm1_expected = 1, cm2_expected = 0;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(move1, 0);
	CPPUNIT_ASSERT_EQUAL(move2, 0);
	CPPUNIT_ASSERT_EQUAL(move3, 2);
}
void
test_chessboard::test_case_12()
{
	chess_board chess;
	std::stringstream s;
	s << "RNBQKBNR" << endl;
	s << "PPPP.PPP" << endl;
	s << "........" << endl;
	s << "....P..." << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "pppppppp" << endl;
	s << "rnbqkbnr" << endl;

	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);

	shared_ptr<chess_piece> cp = chess.get_board().get(1, 7);

	int move1 = cp->valid_move(1, 0);
	int move2 = cp->valid_move(0, 5);
	int move3 = cp->valid_move(2, 5);

	unsigned long cm1_expected = 0, cm2_expected = 0;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(move1, 0);
	CPPUNIT_ASSERT_EQUAL(move2, 1);
	CPPUNIT_ASSERT_EQUAL(move3, 1);
}
void
test_chessboard::test_case_13()
{
	chess_board chess;
	std::stringstream s;
	s << "N..n...." << endl;
	s << "bnp....." << endl;
	s << ".p......" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;
	s << "........" << endl;

	s >> chess;

	vector<chess_move> cm1 = chess.get_capturing_moves(true);
	vector<chess_move> cm2 = chess.get_capturing_moves(false);

	shared_ptr<chess_piece> cp = chess.get_board().get(0, 1);

	int move1 = cp->valid_move(7, 7);
	int move2 = cp->valid_move(1, 0);
	int move3 = cp->valid_move(1, 2);

	unsigned long cm1_expected = 2, cm2_expected = 0;

	CPPUNIT_ASSERT_EQUAL(cm1.size(), cm1_expected);
	CPPUNIT_ASSERT_EQUAL(cm2.size(), cm2_expected);
	CPPUNIT_ASSERT_EQUAL(move1, 0);
	CPPUNIT_ASSERT_EQUAL(move2, 1);
	CPPUNIT_ASSERT_EQUAL(move3, 0);
}
