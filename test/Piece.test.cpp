#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"
#include <typeinfo>


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

TEST(PieceTest, piece_catch_an_enemy)
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
	EXPECT_EQ(board[2].get_piece()->get_color(), PieceColor::white);
}

template <typename T>
void is_in_board(const Square& square, const PieceColor color)
{
	EXPECT_EQ(square.get_piece()->get_color(), color) << "Invalid piece color";
	EXPECT_TRUE( dynamic_cast<T*>(square.get_piece()) ) << "Invalid type of piece";
}


TEST(PieceTest, init_board_game_black_pawn)
{
	BoardGame board;
	board.init_game();
	is_in_board<Pawn>(board[8], PieceColor::black);
	is_in_board<Pawn>(board[9], PieceColor::black);
	is_in_board<Pawn>(board[10], PieceColor::black);
	is_in_board<Pawn>(board[11], PieceColor::black);
	is_in_board<Pawn>(board[12], PieceColor::black);
	is_in_board<Pawn>(board[13], PieceColor::black);
	is_in_board<Pawn>(board[14], PieceColor::black);
	is_in_board<Pawn>(board[15], PieceColor::black);
}

TEST(PieceTest, init_board_game_white_pawn)
{
	BoardGame board;
	board.init_game();
	is_in_board<Pawn>(board[48], PieceColor::white);
	is_in_board<Pawn>(board[49], PieceColor::white);
	is_in_board<Pawn>(board[50], PieceColor::white);
	is_in_board<Pawn>(board[51], PieceColor::white);
	is_in_board<Pawn>(board[52], PieceColor::white);
	is_in_board<Pawn>(board[53], PieceColor::white);
	is_in_board<Pawn>(board[54], PieceColor::white);
	is_in_board<Pawn>(board[55], PieceColor::white);
}

TEST(PieceTest, init_board_game_black_valuable_pieces)
{
	BoardGame board;
	board.init_game();
	is_in_board<Rock>(board[0], PieceColor::black);
	is_in_board<Knight>(board[1], PieceColor::black);
	is_in_board<Bishop>(board[2], PieceColor::black);
	is_in_board<Queen>(board[3], PieceColor::black);
	is_in_board<King>(board[4], PieceColor::black);
	is_in_board<Bishop>(board[5], PieceColor::black);
	is_in_board<Knight>(board[6], PieceColor::black);
	is_in_board<Rock>(board[7], PieceColor::black);
}

TEST(PieceTest, init_board_game_white_valuable_pieces)
{
	BoardGame board;
	board.init_game();
	is_in_board<Rock>(board[56], PieceColor::white);
	is_in_board<Knight>(board[57], PieceColor::white);
	is_in_board<Bishop>(board[58], PieceColor::white);
	is_in_board<Queen>(board[59], PieceColor::white);
	is_in_board<King>(board[60], PieceColor::white);
	is_in_board<Bishop>(board[61], PieceColor::white);
	is_in_board<Knight>(board[62], PieceColor::white);
	is_in_board<Rock>(board[63], PieceColor::white);
}

