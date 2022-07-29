#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(KingSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	auto& knight = board.get_color(0).add_piece<King>(board[11]);
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
	auto& king = board.get_color(0).add_piece<King>(board[63]);
	king.compute_pseudo_legal_squares();
	const auto& king_eligible_squares = king.get_legal_squares();
	EXPECT_EQ(std::count(king_eligible_squares.begin(), king_eligible_squares.end(), nullptr), 61);
	EXPECT_THAT(king_eligible_squares, IsSupersetOf({
		&board[54], &board[55], &board[62] }));
}


TEST(KingSquareAvailableTest, squares_taken)
{
	BoardGame board;
	board.get_color(0).add_piece<MockPiece>(board[18]);
	board.get_color(0).add_piece<MockPiece>(board[3]);
	board.get_color(1).add_piece<MockPiece>(board[2]);
	auto& king = board.get_color(0).add_piece<King>(board[11]);
	king.compute_pseudo_legal_squares();
	const auto& king_eligible_squares = king.get_legal_squares();
	EXPECT_EQ(std::count(king_eligible_squares.begin(), king_eligible_squares.end(), nullptr), 58);
	EXPECT_THAT(king_eligible_squares, IsSupersetOf({
		&board[2],  &board[4], &board[10], &board[12], &board[19],  &board[20]})
		);
}


TEST(KingSquareAvailableTest, squares_attacked)
{
	BoardGame board;
	auto& rock = board.get_color(1).add_piece<Rock>(board[7]);
	auto& king = board.get_color(0).add_piece<King>(board[11]);
	auto& friend_rock = board.get_color(0).add_piece<Rock>(board[21]);
	rock.compute_pseudo_legal_squares();
	king.compute_pseudo_legal_squares();
	friend_rock.compute_pseudo_legal_squares();
	king.compute_legal_squares();
	const auto& king_eligible_squares = king.get_legal_squares();
	EXPECT_EQ(std::count(king_eligible_squares.begin(), king_eligible_squares.end(), nullptr), 59);
	EXPECT_THAT(king_eligible_squares, IsSupersetOf({
		&board[10], &board[12], &board[18] ,&board[19],  &board[20]}));
}


TEST(KingSquareAvailableTest, pawn_attack_squares)
{
	BoardGame board;
	auto& pawn = board.get_color(1).add_piece<Pawn>(board[3]);
	auto& king = board.get_color(0).add_piece<King>(board[19]);
	pawn.compute_pseudo_legal_squares();
	king.compute_pseudo_legal_squares();
	king.compute_legal_squares();
	const auto& king_eligible_squares = king.get_legal_squares();
	EXPECT_EQ(std::count(king_eligible_squares.begin(), king_eligible_squares.end(), nullptr), 58);
	EXPECT_THAT(king_eligible_squares, IsSupersetOf({
		&board[11], &board[18], &board[20], &board[26] ,&board[27],  &board[28]}));
}

