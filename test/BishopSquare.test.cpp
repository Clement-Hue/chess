#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(BishopSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	Bishop bishop{ board, board[11], PieceColor::white };
	bishop.compute_eligible_squares();
	const auto& bishop_eligible_squares = bishop.get_eligible_squares();
	EXPECT_EQ(std::count(bishop_eligible_squares.begin(), bishop_eligible_squares.end(), nullptr), 55);
	EXPECT_THAT(bishop_eligible_squares, IsSupersetOf({
		&board[2], &board[4], &board[18], &board[20], &board[25], &board[29],
		&board[32], &board[38], &board[47] }));
}


TEST(BishopSquareAvailableTest, diagonal_squares_taken)
{
	BoardGame board;
	const MockPiece p1{ board, board[25], PieceColor::white };
	const MockPiece p2{ board, board[38], PieceColor::white };
	const MockPiece p3{ board, board[2], PieceColor::black };
	Bishop bishop{ board, board[11], PieceColor::white };
	bishop.compute_eligible_squares();
	const auto& bishop_eligible_squares = bishop.get_eligible_squares();
	EXPECT_EQ(std::count(bishop_eligible_squares.begin(), bishop_eligible_squares.end(), nullptr), 59);
	EXPECT_THAT(bishop_eligible_squares, IsSupersetOf({
		&board[2], &board[4], &board[18], &board[20], &board[29]
	}));
}

