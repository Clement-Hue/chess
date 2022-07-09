#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(QueenSquareAvailable, all_squares_free)
{
	BoardGame board;
	const Queen queen{ board, board[11], PieceColor::white };
	const auto queen_eligible_squares = queen.get_eligible_squares();
	EXPECT_THAT(queen_eligible_squares, WhenSorted(ElementsAre(
		&board[2],&board[3], &board[4], &board[8], &board[9], &board[10],
		&board[12], &board[13], &board[14], &board[15], &board[18], &board[19],
		&board[20], &board[25], &board[27], &board[29],
		&board[32], &board[35], &board[38],&board[43], &board[47], &board[51],
		&board[59])));
}


TEST(QueenSquareAvailable, squares_taken)
{
	BoardGame board;
	const MockPiece p1{board, board[25], PieceColor::white};
	const MockPiece p2{board, board[38], PieceColor::white};
	const MockPiece p3{board, board[2], PieceColor::black};
	const MockPiece p4{board, board[27], PieceColor::black};
	const Queen queen{ board, board[11], PieceColor::white };
	const auto queen_eligible_squares = queen.get_eligible_squares();
	EXPECT_THAT(queen_eligible_squares, WhenSorted(ElementsAre(
		&board[2],&board[3], &board[4],&board[8], &board[9], &board[10],
		&board[12], &board[13], &board[14], &board[15], &board[18], 
		&board[19], &board[20], &board[27], &board[29]
	 )));
}

