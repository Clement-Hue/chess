#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include <typeinfo>
#include "Matchers.h"


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
	auto& piece = board.get_color(0).add_piece<Pawn>(board[2]);
	EXPECT_EQ(board[2].get_piece(), &piece) << "Pieces are not the same";
}

TEST(PieceTest, link_piece_and_square_when_moving_piece)
{
	BoardGame board;
	auto& piece = board.get_color(0).add_piece<Pawn>(board[2]);
	piece.get_legal_move(4) = std::make_unique<SimpleMove>();
	piece.move(board[4]);
	EXPECT_EQ(board[4].get_piece(), &piece) << "Piece hasn't moved";
	EXPECT_NE(board[2].get_piece(), &piece) << "Piece still present on old square";
}

TEST(PieceTest, piece_catch_an_enemy)
{
	BoardGame board;
	board.set_turn(1);
	auto& black_p = board.get_color(1).add_piece<Pawn>(board[2]);
	const auto& white_p = board.get_color(0).add_piece<Pawn>(board[5]);
	black_p.get_legal_move(5) = std::make_unique<SimpleMove>();
	black_p.move(board[5]);
	EXPECT_EQ(board[5].get_piece(), &black_p) << "Black piece hasn't moved";
	EXPECT_EQ(board[2].get_piece(), nullptr) << "White piece still on the board";
	EXPECT_EQ(black_p.get_square(), &board[5]);
	EXPECT_EQ(white_p.get_square(), nullptr);
}

TEST(PieceTest, cannot_move_to_friend_square)
{
	BoardGame board;
	auto& p1 = board.get_color(0).add_piece<Pawn>(board[2]);
	const auto& p2 = board.get_color(0).add_piece<Pawn>(board[5]);
	p1.move(board[5]);
	EXPECT_EQ(board[5].get_piece(), &p2);
	EXPECT_EQ(board[2].get_piece(), &p1);
	EXPECT_TRUE(board[2].get_piece()->get_color() == WhiteColor(board));;
}


TEST(PieceTest, init_board_game_black_pawn)
{
	BoardGame board;
	board.set_default_pieces();
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
	board.set_default_pieces();
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
	board.set_default_pieces();
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
	board.set_default_pieces();
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

TEST(PieceTest, not_allowed_to_move_to_not_legal_square)
{
	BoardGame board;
	auto& rock = board.get_color(0).add_piece<Rock>(board[40]);
	rock.move(board[48]);
	EXPECT_EQ(rock.get_square(), &board[40]);
	rock.compute_pseudo_legal_moves();
	rock.compute_legal_moves();
	rock.move(board[48]);
	EXPECT_EQ(rock.get_square(), &board[48]);
}

TEST(PieceTest, not_allowed_to_move_if_not_the_turn)
{
	BoardGame board;
	auto& rock = board.get_color(1).add_piece<Rock>(board[40]);
	board.init_game(0);
	rock.move(board[48]);
	EXPECT_EQ(rock.get_square(), &board[40]);
}

TEST(PieceTest, should_have_moved)
{
	BoardGame board;
	auto& rock = board.get_color(0).add_piece<Rock>(board[40]);
	board.init_game();
	EXPECT_FALSE(rock.has_moved());
	rock.move(board[42]);
	EXPECT_EQ(rock.get_square(), &board[42]);
	EXPECT_TRUE(rock.has_moved());
}
