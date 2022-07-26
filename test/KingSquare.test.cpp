#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(KingSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	auto& knight = board.get_color(0).create_piece<King>(&board[11]);
	knight.compute_pseudo_legal_squares();
	const auto& king_eligible_squares = knight.get_legal_squares();
	EXPECT_EQ(std::count(king_eligible_squares.begin(), king_eligible_squares.end(), nullptr), 56);
	EXPECT_THAT(king_eligible_squares, IsSupersetOf({
		&board[2], &board[3], &board[4],
		&board[10], &board[12], &board[18] ,&board[19],  &board[20]}));
}

TEST(KingSquareAvailableTest, positionned_on_edge)
{
	BoardGame board;
	auto& knight = board.get_color(0).create_piece<King>(&board[63]);
	knight.compute_pseudo_legal_squares();
	const auto& king_eligible_squares = knight.get_legal_squares();
	EXPECT_EQ(std::count(king_eligible_squares.begin(), king_eligible_squares.end(), nullptr), 61);
	EXPECT_THAT(king_eligible_squares, IsSupersetOf({
		&board[54], &board[55], &board[62] }));
}


TEST(KingSquareAvailableTest, squares_taken)
{
	BoardGame board;
	board.get_color(0).create_piece<MockPiece>(&board[18]);
	board.get_color(0).create_piece<MockPiece>(&board[3]);
	board.get_color(1).create_piece<MockPiece>(&board[2]);
	auto& king = board.get_color(0).create_piece<King>(&board[11]);
	king.compute_pseudo_legal_squares();
	const auto& king_eligible_squares = king.get_legal_squares();
	EXPECT_EQ(std::count(king_eligible_squares.begin(), king_eligible_squares.end(), nullptr), 58);
	EXPECT_THAT(king_eligible_squares, IsSupersetOf({
		&board[2],  &board[4], &board[10], &board[12], &board[19],  &board[20]})
		);
}

