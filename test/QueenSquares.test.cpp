#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"


TEST(QueenSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	Queen queen{ board, board[11], std::make_unique<WhiteColor>() };
	queen.compute_pseudo_legal_squares();
	const auto& queen_eligible_squares = queen.get_legal_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 41);
	EXPECT_THAT(queen_eligible_squares, IsSupersetOf({
		&board[2],&board[3], &board[4], &board[8], &board[9], &board[10],
		&board[12], &board[13], &board[14], &board[15], &board[18], &board[19],
		&board[20], &board[25], &board[27], &board[29],
		&board[32], &board[35], &board[38],&board[43], &board[47], &board[51],
		&board[59] }));
}


TEST(QueenSquareAvailableTest, squares_taken)
{
	BoardGame board;
	const MockPiece p1{ board, board[25], std::make_unique<WhiteColor>() };
	const MockPiece p2{ board, board[38], std::make_unique<WhiteColor>() };
	const MockPiece p3{ board, board[2], std::make_unique<BlackColor>() };
	const MockPiece p4{ board, board[27], std::make_unique<BlackColor>() };
	Queen queen{ board, board[11], std::make_unique<WhiteColor>() };
	queen.compute_pseudo_legal_squares();
	const auto& queen_eligible_squares = queen.get_legal_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 49);
	EXPECT_THAT(queen_eligible_squares, IsSupersetOf({
		&board[2], &board[3], &board[4], &board[8], &board[9], &board[10],
		&board[12], &board[13], &board[14], &board[15], &board[18],
		&board[19], &board[20], &board[27], &board[29]
	}));
}

