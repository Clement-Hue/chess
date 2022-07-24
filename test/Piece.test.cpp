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
	MockPiece black_p{ board, board[2], std::make_unique<BlackColor>() };
	const MockPiece white_p{ board, board[5], std::make_unique<WhiteColor>() };
	black_p.move(board[5]);
	EXPECT_EQ(board[5].get_piece(), &black_p);
	EXPECT_EQ(board[2].get_piece(), nullptr);
	EXPECT_EQ(black_p.get_square(), &board[5]);
	EXPECT_EQ(white_p.get_square(), nullptr);
}

TEST(PieceTest, cannot_move_to_friend_square)
{
	BoardGame board;
	MockPiece p1{ board, board[2], std::make_unique<WhiteColor>() };
	const MockPiece p2{ board, board[5], std::make_unique<WhiteColor>() };
	p1.move(board[5]);
	EXPECT_EQ(board[5].get_piece(), &p2);
	EXPECT_EQ(board[2].get_piece(), &p1);
	EXPECT_EQ(board[2].get_piece()->get_color(), WhiteColor());
}

template <typename T, typename Color>
void is_in_board(const Square& square )
{
	EXPECT_EQ(typeid(square.get_piece()->get_color()), typeid(Color)) << "Invalid piece color";
	EXPECT_TRUE( dynamic_cast<T*>(square.get_piece()) ) << "Invalid type of piece";
}


TEST(PieceTest, init_board_game_black_pawn)
{
	BoardGame board;
	board.init_game();
	is_in_board<Pawn, BlackColor>(board[8]);
	is_in_board<Pawn, BlackColor>(board[9]);
	is_in_board<Pawn, BlackColor>(board[10]);
	is_in_board<Pawn, BlackColor>(board[11]);
	is_in_board<Pawn, BlackColor>(board[12]);
	is_in_board<Pawn, BlackColor>(board[13]);
	is_in_board<Pawn, BlackColor>(board[14]);
	is_in_board<Pawn, BlackColor>(board[15]);
}

TEST(PieceTest, init_board_game_white_pawn)
{
	BoardGame board;
	board.init_game();
	is_in_board<Pawn, WhiteColor>(board[48]);
	is_in_board<Pawn, WhiteColor>(board[49]);
	is_in_board<Pawn, WhiteColor>(board[50]);
	is_in_board<Pawn, WhiteColor>(board[51]);
	is_in_board<Pawn, WhiteColor>(board[52]);
	is_in_board<Pawn, WhiteColor>(board[53]);
	is_in_board<Pawn, WhiteColor>(board[54]);
	is_in_board<Pawn, WhiteColor>(board[55]);
}

TEST(PieceTest, init_board_game_black_valuable_pieces)
{
	BoardGame board;
	board.init_game();
	is_in_board<Rock, BlackColor>(board[0]);
	is_in_board<Knight, BlackColor>(board[1]);
	is_in_board<Bishop, BlackColor>(board[2]);
	is_in_board<Queen, BlackColor>(board[3]);
	is_in_board<King, BlackColor>(board[4]);
	is_in_board<Bishop, BlackColor>(board[5]);
	is_in_board<Knight, BlackColor>(board[6]);
	is_in_board<Rock, BlackColor>(board[7]);
}

TEST(PieceTest, init_board_game_white_valuable_pieces)
{
	BoardGame board;
	board.init_game();
	is_in_board<Rock, WhiteColor>(board[56]);
	is_in_board<Knight, WhiteColor>(board[57]);
	is_in_board<Bishop, WhiteColor>(board[58]);
	is_in_board<Queen, WhiteColor>(board[59]);
	is_in_board<King, WhiteColor>(board[60]);
	is_in_board<Bishop, WhiteColor>(board[61]);
	is_in_board<Knight, WhiteColor>(board[62]);
	is_in_board<Rock, WhiteColor>(board[63]);
}

TEST(PieceColorTest, color_equality)
{
	const BlackColor black;
	const WhiteColor white;
	const PieceColor* pt_color = &black;
	EXPECT_TRUE(*pt_color == BlackColor());
	pt_color = &white;
	EXPECT_TRUE(*pt_color != BlackColor());
	EXPECT_TRUE(WhiteColor() == WhiteColor());
	EXPECT_TRUE(WhiteColor() != BlackColor());
	EXPECT_FALSE(WhiteColor() == BlackColor());
}
