#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"
#include "game/PieceColor.h"

TEST(RockSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	Rock& rock = board.get_color(0).add_piece<Rock>(board[11]);
	rock.compute_pseudo_legal_squares();
	const auto& rock_eligible_squares = rock.get_legal_squares();
	EXPECT_EQ(std::count(rock_eligible_squares.begin(), rock_eligible_squares.end(), nullptr), 50);
	EXPECT_THAT(rock_eligible_squares, IsSupersetOf({
		&board[3], &board[8], &board[9], &board[10], &board[12], &board[13],
		&board[14], &board[15], &board[19], &board[27], &board[35], &board[43],
		&board[51], &board[59]
		}));
}

TEST(RockSquareAvailableTest, rock_on_first_line)
{
	BoardGame board;
	Rock& rock = board.get_color(0).add_piece<Rock>(board[3]);
	rock.compute_pseudo_legal_squares();
	const auto& rock_eligible_squares = rock.get_legal_squares();
	EXPECT_EQ(std::count(rock_eligible_squares.begin(), rock_eligible_squares.end(), nullptr), 50);
	EXPECT_THAT(rock_eligible_squares, IsSupersetOf({
		&board[0], &board[1], &board[2], &board[4], &board[5], &board[6],
		&board[7], &board[11], &board[19], &board[27], &board[35], &board[43],
		&board[51], &board[59]
	}));
}


TEST(RockSquareAvailableTest, rock_on_edge)
{
	BoardGame board;
	Rock& rock = board.get_color(0).add_piece<Rock>(board[63]);
	rock.compute_pseudo_legal_squares();
	const auto &rock_eligible_squares = rock.get_legal_squares();
	EXPECT_EQ(std::count(rock_eligible_squares.begin(), rock_eligible_squares.end(), nullptr), 50);
	EXPECT_THAT(rock_eligible_squares, IsSupersetOf({
		&board[7], &board[15], &board[23], &board[31], &board[39], &board[47],
		&board[55], &board[56], &board[57], &board[58], &board[59], &board[60],
		&board[61], &board[62]
	}));
}

TEST(RockSquareAvailableTest, left_square_taken)
{
	BoardGame board;
	const auto& piece = board.get_color(0).add_piece<MockPiece>(board[10]);
	auto& rock = board.get_color(0).add_piece<Rock>(board[11]);
	rock.compute_pseudo_legal_squares();
	const auto& rock_eligible_squares = rock.get_legal_squares();
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[8])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[9])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[10])));
}

TEST(RockSquareAvailableTest, right_square_taken)
{
	BoardGame board;
	const auto& piece = board.get_color(0).add_piece<MockPiece>(board[12]);
	auto& rock = board.get_color(0).add_piece<Rock>(board[11]);
	rock.compute_pseudo_legal_squares();
	const auto& rock_eligible_squares = rock.get_legal_squares();
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[12])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[13])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[14])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[15])));
}

TEST(RockSquareAvailableTest, upper_square_taken)
{
	BoardGame board;
	board.get_color(0).add_piece<MockPiece>(board[41]);
	auto& rock = board.get_color(0).add_piece<Rock>(board[25]);
	rock.compute_pseudo_legal_squares();
	const auto& rock_eligible_squares = rock.get_legal_squares();
	EXPECT_THAT(rock_eligible_squares ,Contains(&board[33]));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[41])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[49])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[58])));
}

TEST(RockSquareAvailableTest, lower_square_taken)
{
	BoardGame board;
	board.get_color(0).add_piece<MockPiece>(board[3]);
	auto& rock = board.get_color(0).add_piece<Rock>(board[19]);
	rock.compute_pseudo_legal_squares();
	const auto& rock_eligible_squares = rock.get_legal_squares();
	EXPECT_THAT(rock_eligible_squares ,Contains(&board[11]));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[3])));
}

TEST(RockSquareAvailableTest, enemy_squares_are_available_squares)
{
	BoardGame board;
	const auto& p1 = board.get_color(1).add_piece<MockPiece>(board[3]);
	const auto& p2 = board.get_color(1).add_piece<MockPiece>(board[27]);
	const auto& p3 = board.get_color(1).add_piece<MockPiece>(board[18]);
	const auto& p4 = board.get_color(1).add_piece<MockPiece>(board[20]);
	auto& rock = board.get_color(0).add_piece<Rock>(board[19]);
	rock.compute_pseudo_legal_squares();
	const auto& rock_eligible_squares = rock.get_legal_squares();
	EXPECT_THAT(rock_eligible_squares, IsSupersetOf({
		p1.get_square(), p2.get_square(), p3.get_square(), p4.get_square()
	}));
}
