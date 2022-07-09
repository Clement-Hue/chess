#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(KnightSquareAvailable, all_squares_free)
{
	BoardGame board;
	const Knight knight{ board, board[11], PieceColor::white };
	const auto knight_eligible_squares = knight.get_eligible_squares();
	EXPECT_EQ(std::count(knight_eligible_squares.begin(), knight_eligible_squares.end(), nullptr), 56);
	EXPECT_THAT(knight_eligible_squares, IsSupersetOf({
		&board[2], &board[3], &board[4],
		&board[10], &board[12], &board[18] ,&board[19],  &board[20]}));
}


TEST(KnightSquareAvailable, squares_taken)
{
	BoardGame board;
	const MockPiece p1{ board, board[18], PieceColor::white };
	const MockPiece p2{ board, board[3], PieceColor::white };
	const MockPiece p3{ board, board[2], PieceColor::black };
	const Knight knight{ board, board[11], PieceColor::white };
	const auto knight_eligible_squares = knight.get_eligible_squares();
	EXPECT_EQ(std::count(knight_eligible_squares.begin(), knight_eligible_squares.end(), nullptr), 58);
	EXPECT_THAT(knight_eligible_squares, IsSupersetOf({
		&board[2],  &board[4], &board[10], &board[12], &board[19],  &board[20]})
		);
}

