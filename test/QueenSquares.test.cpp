#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"


TEST(QueenSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	auto& queen = board.get_color(0).add_piece<Queen>(board[11]);
	queen.compute_pseudo_legal_squares();
	const auto& queen_eligible_squares = queen.get_legal_squares();
	has_squares(queen_eligible_squares, { 2,3,4,8,9,10,12,13,14,15,18,19,20,
		25,27,29,32,35,38,43,47,51,59 });
}


TEST(QueenSquareAvailableTest, squares_taken)
{
	BoardGame board;
	board.get_color(0).add_piece<MockPiece>(board[25]);
	board.get_color(0).add_piece<MockPiece>(board[38]);
	board.get_color(1).add_piece<MockPiece>(board[2]);
	board.get_color(1).add_piece<MockPiece>(board[27]);
	auto& queen = board.get_color(0).add_piece<Queen>(board[11]);
	queen.compute_pseudo_legal_squares();
	const auto& queen_eligible_squares = queen.get_legal_squares();
	has_squares(queen_eligible_squares, { 2,3,4,8,9,10,12,13,14,15,18,19,20,27,29 });
}

