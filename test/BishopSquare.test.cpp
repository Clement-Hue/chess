#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(BishopSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	auto& bishop = board.get_color(0).add_piece<Bishop>(board[11]);
	bishop.compute_pseudo_legal_squares();
	const auto& bishop_eligible_squares = bishop.get_legal_squares();
	has_squares(bishop_eligible_squares, { 2,4,18,20,25,29,32,38,47 });
}


TEST(BishopSquareAvailableTest, diagonal_squares_taken)
{
	BoardGame board;
	board.get_color(0).add_piece<MockPiece>(board[25]);
	board.get_color(0).add_piece<MockPiece>(board[38]);
	board.get_color(1).add_piece<MockPiece>(board[2]);
	auto& bishop = board.get_color(0).add_piece<Bishop>(board[11]);
	bishop.compute_pseudo_legal_squares();
	const auto& bishop_eligible_squares = bishop.get_legal_squares();
	has_squares(bishop_eligible_squares, { 2,4,18,20,29 });
}

