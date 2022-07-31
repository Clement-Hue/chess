#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"
#include "game/Piece.h"


TEST(PinTest, piece_pinned_on_rank)
{
	BoardGame board;
	board.get_color(0).add_piece<King>(board[13]);
	board.get_color(1).add_piece<Rock>(board[45]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[29]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_moves();
	has_squares(queen_eligible_squares, { 21,37,45 });
}


TEST(PinTest, piece_pinned_on_file)
{
	BoardGame board;
	board.get_color(0).add_piece<King>(board[8]);
	board.get_color(1).add_piece<Rock>(board[15]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[14]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_moves();
	has_squares(queen_eligible_squares, { 9,10,11,12,13,15 });
}


TEST(PinTest, piece_pinned_on_diagonal)
{
	BoardGame board;
	board.get_color(0).add_piece<King>(board[14]);
	board.get_color(1).add_piece<Bishop>(board[42]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[28]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_moves();
	has_squares(queen_eligible_squares, { 21,35,42 });
}

TEST(PinTest, piece_pinned_on_anti_diagonal)
{
	BoardGame board;
	board.get_color(0).add_piece<King>(board[9]);
	board.get_color(1).add_piece<Bishop>(board[54]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[27]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_moves();
	has_squares(queen_eligible_squares, { 18,36,45,54 });
}

TEST(PinTest, not_pinned_if_friend_piece_between)
{
	BoardGame board;
	board.get_color(0).add_piece<King>(board[9]);
	board.get_color(0).add_piece<Pawn>(board[18]);
	board.get_color(1).add_piece<Bishop>(board[54]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[27]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_moves();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 41);
}


TEST(PinTest, not_pinned_if_enemy_piece_between)
{
	BoardGame board;
	board.get_color(0).add_piece<King>(board[9]);
	board.get_color(1).add_piece<Pawn>(board[18]);
	board.get_color(1).add_piece<Bishop>(board[54]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[27]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_moves();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 40);
}


TEST(PinTest, should_unpinned_if_king_move)
{
	BoardGame board;
	auto& king = board.get_color(0).add_piece<King>(board[9]);
	auto& bishop = board.get_color(1).add_piece<Bishop>(board[54]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[27]);
	board.init_game();
	auto* queen_legal_squares = &queen.get_legal_moves();
	EXPECT_EQ(std::count(queen_legal_squares->begin(), queen_legal_squares->end(), nullptr), 60);
	king.move(board[8]);
	queen_legal_squares = &queen.get_legal_moves();
	bishop.move(board[63]);
	EXPECT_EQ(std::count(queen_legal_squares->begin(), queen_legal_squares->end(), nullptr), 37);
}


TEST(PinTest, pin_black_piece)
{
	BoardGame board;
	board.get_color(1).add_piece<King>(board[9]);
	board.get_color(0).add_piece<Bishop>(board[54]);
	const auto& queen = board.get_color(1).add_piece<Queen>(board[27]);
	board.init_game(1);
	const auto& queen_legal_squares = queen.get_legal_moves();
	has_squares(queen_legal_squares, { 18,36,45,54 });
}
