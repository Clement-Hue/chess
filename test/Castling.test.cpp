#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"

TEST(CastlingTest, castle_if_no_pieces_between_rock_and_king)
{
	BoardGame board;
	const auto& king = board.get_color(0).add_piece<King>(board[60]);
	board.get_color(0).add_piece<Rock>(board[63]);
	board.get_color(0).add_piece<Rock>(board[6]);
	board.init_game();
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_TRUE(king_legal_moves[63]);
}


TEST(CastlingTest, long_castle_if_no_pieces_between_rock_and_king)
{
	BoardGame board;
	const auto& king = board.get_color(0).add_piece<King>(board[60]);
	board.get_color(0).add_piece<Rock>(board[56]);
	board.init_game();
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_TRUE(king_legal_moves[56]);
}

TEST(CastlingTest, no_castle_if_rock_is_enemy)
{
	BoardGame board;
	const auto& king = board.get_color(0).add_piece<King>(board[60]);
	board.get_color(1).add_piece<Rock>(board[63]);
	board.init_game();
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_FALSE(king_legal_moves[63]);
}


TEST(CastlingTest, no_castle_if_piece_between)
{
	BoardGame board;
	const auto& king = board.get_color(0).add_piece<King>(board[60]);
	board.get_color(0).add_piece<Bishop>(board[62]);
	board.get_color(0).add_piece<Rock>(board[63]);
	board.init_game();
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_FALSE(king_legal_moves[63]);
}

TEST(CastlingTest, no_castle_if_king_has_moved)
{
	BoardGame board;
	auto& bishop_b = board.get_color(1).add_piece<Bishop>(board[10]);
	auto& king = board.get_color(0).add_piece<King>(board[59]);
	board.get_color(0).add_piece<Rock>(board[63]);
	board.init_game();
	king.move(board[60]);
	bishop_b.move(board[19]);
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_FALSE(king_legal_moves[63]);
}

TEST(CastlingTest, no_castle_if_rock_has_moved)
{
	BoardGame board;
	auto& bishop_b = board.get_color(1).add_piece<Bishop>(board[10]);
	const auto& king = board.get_color(0).add_piece<King>(board[60]);
	auto& rock = board.get_color(0).add_piece<Rock>(board[62]);
	board.init_game();
	rock.move(board[63]);
	bishop_b.move(board[19]);
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_FALSE(king_legal_moves[63]);
}

TEST(CastlingTest, no_castle_if_king_is_not_on_start_position)
{
	BoardGame board;
	const auto& king = board.get_color(0).add_piece<King>(board[59]);
	board.get_color(0).add_piece<Rock>(board[63]);
	board.init_game();
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_FALSE(king_legal_moves[63]);
}

TEST(CastlingTest, no_castle_if_rock_is_not_on_start_position)
{
	BoardGame board;
	const auto& king = board.get_color(0).add_piece<King>(board[60]);
	board.get_color(0).add_piece<Rock>(board[62]);
	board.init_game();
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_FALSE(king_legal_moves[62]);
}


TEST(CastlingTest, no_castle_if_king_pass_through_attacked_squares)
{
	BoardGame board;
	const auto& king = board.get_color(0).add_piece<King>(board[60]);
	board.get_color(1).add_piece<Rock>(board[2]);
	board.get_color(0).add_piece<Rock>(board[56]);
	board.init_game();
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_FALSE(king_legal_moves[56]);
}

TEST(CastlingTest, castle_if_king_dont_pass_through_attacked_squares)
{
	BoardGame board;
	const auto& king = board.get_color(0).add_piece<King>(board[60]);
	board.get_color(1).add_piece<Rock>(board[1]);
	board.get_color(0).add_piece<Rock>(board[56]);
	board.init_game();
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_TRUE(king_legal_moves[56]);
}


TEST(CastlingTest, no_castle_if_king_is_under_attacked)
{
	BoardGame board;
	const auto& king = board.get_color(0).add_piece<King>(board[60]);
	board.get_color(1).add_piece<Rock>(board[4]);
	board.get_color(0).add_piece<Rock>(board[56]);
	board.init_game();
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_FALSE(king_legal_moves[56]);
}

TEST(CastlingTest, castle_if_rock_is_under_attacked)
{
	BoardGame board;
	const auto& king = board.get_color(0).add_piece<King>(board[60]);
	board.get_color(1).add_piece<Rock>(board[0]);
	board.get_color(0).add_piece<Rock>(board[56]);
	board.init_game();
	const auto& king_legal_moves = king.get_legal_moves();
	EXPECT_TRUE(king_legal_moves[56]);
}

TEST(CastlingTest, move_the_king_and_rock_when_castling)
{
	BoardGame board;
	auto& king = board.get_color(0).add_piece<King>(board[60]);
	const auto& rock = board.get_color(0).add_piece<Rock>(board[63]);
	board.init_game();
	king.move(board[63]);
	EXPECT_EQ(king.get_square(), &board[62]);
	EXPECT_EQ(board[62].get_piece(), &king);
	EXPECT_EQ(rock.get_square(), &board[61]);
	EXPECT_EQ(board[61].get_piece(), &rock);
	EXPECT_EQ(board[60].get_piece(), nullptr);
	EXPECT_EQ(board[63].get_piece(), nullptr);
	EXPECT_TRUE(king.has_moved());
	EXPECT_TRUE(rock.has_moved());
}
