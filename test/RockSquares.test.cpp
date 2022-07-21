#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(RockSquareAvailable, all_squares_free)
{
	BoardGame board;
	Rock rock{ board, board[11], PieceColor::white };
	rock.compute_eligible_squares();
	const auto& rock_eligible_squares = rock.get_eligible_squares();
	EXPECT_EQ(std::count(rock_eligible_squares.begin(), rock_eligible_squares.end(), nullptr), 50);
	EXPECT_THAT(rock_eligible_squares, IsSupersetOf({
		&board[3], &board[8], &board[9], &board[10], &board[12], &board[13],
		&board[14], &board[15], &board[19], &board[27], &board[35], &board[43],
		&board[51], &board[59]
		}));
}

TEST(RockSquareAvailable, rock_on_first_line)
{
	BoardGame board;
	Rock rock{ board, board[3], PieceColor::white };
	rock.compute_eligible_squares();
	const auto& rock_eligible_squares = rock.get_eligible_squares();
	EXPECT_EQ(std::count(rock_eligible_squares.begin(), rock_eligible_squares.end(), nullptr), 50);
	EXPECT_THAT(rock_eligible_squares, IsSupersetOf({
		&board[0], &board[1], &board[2], &board[4], &board[5], &board[6],
		&board[7], &board[11], &board[19], &board[27], &board[35], &board[43],
		&board[51], &board[59]
	}));
}


TEST(RockSquareAvailable, rock_on_edge)
{
	BoardGame board;
	Rock rock{ board, board[63], PieceColor::white };
	rock.compute_eligible_squares();
	const auto &rock_eligible_squares = rock.get_eligible_squares();
	EXPECT_EQ(std::count(rock_eligible_squares.begin(), rock_eligible_squares.end(), nullptr), 50);
	EXPECT_THAT(rock_eligible_squares, IsSupersetOf({
		&board[7], &board[15], &board[23], &board[31], &board[39], &board[47],
		&board[55], &board[56], &board[57], &board[58], &board[59], &board[60],
		&board[61], &board[62]
	}));
}

TEST(RockSquareAvailable, left_square_taken)
{
	BoardGame board;
	const MockPiece piece{board, board[10]};
	Rock rock{ board, board[11], PieceColor::white };
	rock.compute_eligible_squares();
	const auto& rock_eligible_squares = rock.get_eligible_squares();
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[8])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[9])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[10])));
}

TEST(RockSquareAvailable, right_square_taken)
{
	BoardGame board;
	const MockPiece piece{board, board[12]};
	Rock rock{ board, board[11], PieceColor::white };
	rock.compute_eligible_squares();
	const auto& rock_eligible_squares = rock.get_eligible_squares();
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[12])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[13])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[14])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[15])));
}

TEST(RockSquareAvailable, upper_square_taken)
{
	BoardGame board;
	const MockPiece piece{board, board[41]};
	Rock rock{ board, board[25], PieceColor::white };
	rock.compute_eligible_squares();
	const auto& rock_eligible_squares = rock.get_eligible_squares();
	EXPECT_THAT(rock_eligible_squares ,Contains(&board[33]));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[41])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[49])));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[58])));
}

TEST(RockSquareAvailable, lower_square_taken)
{
	BoardGame board;
	const MockPiece piece{board, board[3]};
	Rock rock{ board, board[19], PieceColor::white };
	rock.compute_eligible_squares();
	const auto& rock_eligible_squares = rock.get_eligible_squares();
	EXPECT_THAT(rock_eligible_squares ,Contains(&board[11]));
	EXPECT_THAT(rock_eligible_squares ,Not(Contains(&board[3])));
}

TEST(RockSquareAvailable, enemy_squares_are_available_squares)
{
	BoardGame board;
	const MockPiece p1 = { board, board[3], PieceColor::black };
	const MockPiece p2 = {board, board[27], PieceColor::black};
	const MockPiece p3 = {board, board[18], PieceColor::black};
	const MockPiece p4 = { board, board[20], PieceColor::black };
	Rock rock{ board, board[19], PieceColor::white };
	rock.compute_eligible_squares();
	const auto& rock_eligible_squares = rock.get_eligible_squares();
	EXPECT_THAT(rock_eligible_squares, IsSupersetOf({
		p1.get_square(), p2.get_square(), p3.get_square(), p4.get_square()
	}));
}
