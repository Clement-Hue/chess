#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"


TEST(PinTest, piece_pinned_on_rank)
{
	BoardGame board;
	board.get_color(0).add_piece<King>(board[13]);
	board.get_color(1).add_piece<Rock>(board[45]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[29]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 61);
	EXPECT_THAT(queen_eligible_squares, IsSupersetOf({
		&board[21], &board[37], &board[45]})
	);
}


TEST(PinTest, piece_pinned_on_file)
{
	BoardGame board;
	board.get_color(0).add_piece<King>(board[8]);
	board.get_color(1).add_piece<Rock>(board[15]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[14]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 58);
	EXPECT_THAT(queen_eligible_squares, IsSupersetOf({
		&board[9], &board[10], &board[11], &board[12], &board[13], &board[15]})
	);
}


TEST(PinTest, piece_pinned_on_diagonal)
{
	BoardGame board;
	board.get_color(0).add_piece<King>(board[14]);
	board.get_color(1).add_piece<Bishop>(board[42]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[28]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 61);
	EXPECT_THAT(queen_eligible_squares, IsSupersetOf({
		&board[21], &board[35], &board[42] })
	);
}

TEST(PinTest, piece_pinned_on_anti_diagonal)
{
	BoardGame board;
	board.get_color(0).add_piece<King>(board[9]);
	board.get_color(1).add_piece<Bishop>(board[54]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[27]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 60);
	EXPECT_THAT(queen_eligible_squares, IsSupersetOf({
		&board[18], &board[36], &board[45], &board[54]})
	);
}

TEST(PinTest, not_pinned_if_friend_piece_between)
{
	BoardGame board;
	board.get_color(0).add_piece<King>(board[9]);
	board.get_color(0).add_piece<Pawn>(board[18]);
	board.get_color(1).add_piece<Bishop>(board[54]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[27]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_squares();
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
	const auto& queen_eligible_squares = queen.get_legal_squares();
	EXPECT_EQ(std::count(queen_eligible_squares.begin(), queen_eligible_squares.end(), nullptr), 40);
}


TEST(PinTest, should_unpinned_if_king_move)
{
	BoardGame board;
	auto& king = board.get_color(0).add_piece<King>(board[9]);
	auto& bishop = board.get_color(1).add_piece<Bishop>(board[54]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[27]);
	board.init_game();
	auto* queen_legal_squares = &queen.get_legal_squares();
	EXPECT_EQ(std::count(queen_legal_squares->begin(), queen_legal_squares->end(), nullptr), 60);
	king.move(board[8]);
	queen_legal_squares = &queen.get_legal_squares();
	bishop.move(board[63]);
	EXPECT_EQ(std::count(queen_legal_squares->begin(), queen_legal_squares->end(), nullptr), 37);
}
