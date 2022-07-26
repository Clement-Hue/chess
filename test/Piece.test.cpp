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
	auto& piece = board.get_color(0).create_piece<MockPiece>(&board[2]);
	EXPECT_EQ(board[2].get_piece(), &piece) << "Pieces are not the same";
}

TEST(PieceTest, link_piece_and_square_when_moving_piece)
{
	BoardGame board;
	auto& piece = board.get_color(0).create_piece<MockPiece>(&board[2]);
	piece.move(board[4]);
	EXPECT_EQ(board[4].get_piece(), &piece) << "Piece hasn't moved";
	EXPECT_NE(board[2].get_piece(), &piece) << "Piece still present on old square";
}

TEST(PieceTest, piece_catch_an_enemy)
{
	BoardGame board;
	auto& black_p = board.get_color(1).create_piece<MockPiece>(&board[2]);
	const auto& white_p = board.get_color(0).create_piece<MockPiece>(&board[5]);
	black_p.move(board[5]);
	EXPECT_EQ(board[5].get_piece(), &black_p);
	EXPECT_EQ(board[2].get_piece(), nullptr);
	EXPECT_EQ(black_p.get_square(), &board[5]);
	EXPECT_EQ(white_p.get_square(), nullptr);
}

TEST(PieceTest, cannot_move_to_friend_square)
{
	BoardGame board;
	auto& p1 = board.get_color(0).create_piece<MockPiece>(&board[2]);
	const auto& p2 = board.get_color(0).create_piece<MockPiece>(&board[5]);
	p1.move(board[5]);
	EXPECT_EQ(board[5].get_piece(), &p2);
	EXPECT_EQ(board[2].get_piece(), &p1);
	EXPECT_TRUE(board[2].get_piece()->get_color() == WhiteColor(board));;
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
	BoardGame board;
	const PieceColor* pt_color = &board.get_color(1);
	EXPECT_TRUE(*pt_color == BlackColor(board));
	pt_color = &board.get_color(0);
	EXPECT_TRUE(*pt_color != BlackColor(board));
	EXPECT_TRUE(WhiteColor(board) == WhiteColor(board));
	EXPECT_TRUE(WhiteColor(board) != BlackColor(board));
	EXPECT_FALSE(WhiteColor(board) == BlackColor(board));
}
