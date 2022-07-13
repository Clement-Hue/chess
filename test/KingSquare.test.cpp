#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(KingSquareAvailable, all_squares_free)
{
	BoardGame board;
	const King knight{ board, board[11], PieceColor::white };
	const auto king_eligible_squares = knight.get_eligible_squares();
	EXPECT_EQ(std::count(king_eligible_squares.begin(), king_eligible_squares.end(), nullptr), 56);
	EXPECT_THAT(king_eligible_squares, IsSupersetOf({
		&board[2], &board[3], &board[4],
		&board[10], &board[12], &board[18] ,&board[19],  &board[20]}));
}

TEST(KingSquareAvailable, positionned_on_edge)
{
	BoardGame board;
	const King knight{ board, board[63], PieceColor::white };
	const auto king_eligible_squares = knight.get_eligible_squares();
	EXPECT_EQ(std::count(king_eligible_squares.begin(), king_eligible_squares.end(), nullptr), 61);
	EXPECT_THAT(king_eligible_squares, IsSupersetOf({
		&board[54], &board[55], &board[62] }));
}


TEST(KingSquareAvailable, squares_taken)
{
	BoardGame board;
	const MockPiece p1{ board, board[18], PieceColor::white };
	const MockPiece p2{ board, board[3], PieceColor::white };
	const MockPiece p3{ board, board[2], PieceColor::black };
	const King king{ board, board[11], PieceColor::white };
	const auto king_eligible_squares = king.get_eligible_squares();
	EXPECT_EQ(std::count(king_eligible_squares.begin(), king_eligible_squares.end(), nullptr), 58);
	EXPECT_THAT(king_eligible_squares, IsSupersetOf({
		&board[2],  &board[4], &board[10], &board[12], &board[19],  &board[20]})
		);
}
