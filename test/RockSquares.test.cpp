#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "game/PieceColor.h"

TEST(RockSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	Rock& rock = board.get_color(0).add_piece<Rock>(board[11]);
	rock.compute_pseudo_legal_moves();
	const auto& rock_eligible_squares = rock.get_legal_moves();
	has_squares(rock_eligible_squares, {3, 8,9,10,12,13,14,15,19,27,35,43,51,59 });
}

TEST(RockSquareAvailableTest, rock_on_first_line)
{
	BoardGame board;
	Rock& rock = board.get_color(0).add_piece<Rock>(board[3]);
	rock.compute_pseudo_legal_moves();
	const auto& rock_eligible_squares = rock.get_legal_moves();
	has_squares(rock_eligible_squares, { 0,1,2,4,5,6,7,11,19,27,35,43,51,59 });
}


TEST(RockSquareAvailableTest, rock_on_edge)
{
	BoardGame board;
	Rock& rock = board.get_color(0).add_piece<Rock>(board[63]);
	rock.compute_pseudo_legal_moves();
	const auto &rock_eligible_squares = rock.get_legal_moves();
	has_squares(rock_eligible_squares, { 7,15,23,31,39,47,55,56,57,58,59,60,61,62 });
}

TEST(RockSquareAvailableTest, left_square_taken)
{
	BoardGame board;
	board.get_color(0).add_piece<Pawn>(board[10]);
	auto& rock = board.get_color(0).add_piece<Rock>(board[11]);
	rock.compute_pseudo_legal_moves();
	const auto& rock_eligible_squares = rock.get_legal_moves();
	EXPECT_FALSE(rock_eligible_squares[8]);
	EXPECT_FALSE(rock_eligible_squares[9]);
	EXPECT_FALSE(rock_eligible_squares[10]);
}

TEST(RockSquareAvailableTest, right_square_taken)
{
	BoardGame board;
	const auto& piece = board.get_color(0).add_piece<Pawn>(board[12]);
	auto& rock = board.get_color(0).add_piece<Rock>(board[11]);
	rock.compute_pseudo_legal_moves();
	const auto& rock_eligible_squares = rock.get_legal_moves();
	EXPECT_FALSE(rock_eligible_squares[12]);
	EXPECT_FALSE(rock_eligible_squares[13]);
	EXPECT_FALSE(rock_eligible_squares[14]);
	EXPECT_FALSE(rock_eligible_squares[15]);
}

TEST(RockSquareAvailableTest, upper_square_taken)
{
	BoardGame board;
	board.get_color(0).add_piece<Pawn>(board[41]);
	auto& rock = board.get_color(0).add_piece<Rock>(board[25]);
	rock.compute_pseudo_legal_moves();
	const auto& rock_eligible_squares = rock.get_legal_moves();
	EXPECT_TRUE(rock_eligible_squares[33]);
	EXPECT_FALSE(rock_eligible_squares[41]);
	EXPECT_FALSE(rock_eligible_squares[49]);
	EXPECT_FALSE(rock_eligible_squares[58]);
}

TEST(RockSquareAvailableTest, lower_square_taken)
{
	BoardGame board;
	board.get_color(0).add_piece<Pawn>(board[3]);
	auto& rock = board.get_color(0).add_piece<Rock>(board[19]);
	rock.compute_pseudo_legal_moves();
	const auto& rock_eligible_squares = rock.get_legal_moves();
	EXPECT_TRUE(rock_eligible_squares[11]);
	EXPECT_FALSE(rock_eligible_squares[3]);
}

TEST(RockSquareAvailableTest, enemy_squares_are_available_squares)
{
	BoardGame board;
	const auto& p1 = board.get_color(1).add_piece<Pawn>(board[3]);
	const auto& p2 = board.get_color(1).add_piece<Pawn>(board[27]);
	const auto& p3 = board.get_color(1).add_piece<Pawn>(board[18]);
	const auto& p4 = board.get_color(1).add_piece<Pawn>(board[20]);
	auto& rock = board.get_color(0).add_piece<Rock>(board[19]);
	rock.compute_pseudo_legal_moves();
	const auto& rock_eligible_squares = rock.get_legal_moves();
	EXPECT_TRUE(rock_eligible_squares[p1.get_square()->get_value()]);
	EXPECT_TRUE(rock_eligible_squares[p2.get_square()->get_value()]);
	EXPECT_TRUE(rock_eligible_squares[p3.get_square()->get_value()]);
	EXPECT_TRUE(rock_eligible_squares[p4.get_square()->get_value()]);
}
