#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"


TEST(BoardGameTest, construct_board_squares)
{
	BoardGame board;
	for (uint8_t i = 0; i< 64 ; ++i)
	{
		EXPECT_EQ(board[i].get_value(), i);
	}
}

TEST(PieceTest, link_piece_and_square_on_construct)
{
	BoardGame board;
	const MockPiece piece{ board, board[2] };
	EXPECT_EQ(board[2].get_piece(), &piece) << "Pieces are not the same";
}

TEST(PieceTest, link_piece_and_square_when_moving_piece)
{
	BoardGame board;
	MockPiece piece{ board, board[2] };
	piece.move(board[4]);
	EXPECT_EQ(board[4].get_piece(), &piece) << "Piece hasn't moved";
	EXPECT_NE(board[2].get_piece(), &piece) << "Piece still present on old square";
}

TEST(PieceTest, piece_take_square_of_an_enemy)
{
	BoardGame board;
	MockPiece black_p{ board, board[2], PieceColor::black };
	const MockPiece white_p{ board, board[5], PieceColor::white };
	black_p.move(board[5]);
	EXPECT_EQ(board[5].get_piece(), &black_p);
	EXPECT_EQ(board[2].get_piece(), nullptr);
	EXPECT_EQ(black_p.get_square(), &board[5]);
	EXPECT_EQ(white_p.get_square(), nullptr);
}

TEST(PieceTest, cannot_move_to_friend_square)
{
	BoardGame board;
	MockPiece p1{ board, board[2], PieceColor::white };
	const MockPiece p2{ board, board[5], PieceColor::white };
	p1.move(board[5]);
	EXPECT_EQ(board[5].get_piece(), &p2);
	EXPECT_EQ(board[2].get_piece(), &p1);
}
