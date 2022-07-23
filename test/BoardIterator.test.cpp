#include "pch.h"
#include "game/BoardGame.h"
#include "game/BoardIterator.h"


TEST(RankIteration, add_operator)
{
	BoardGame board;
	RankIterator rank_iterator{ board };
	auto& iterator = rank_iterator.begin(board[0]);
	++iterator;
	EXPECT_EQ(iterator->get_value(), 1);
	iterator += 3;
	EXPECT_EQ(iterator->get_value(), 4);
	iterator += 4;
	EXPECT_FALSE(iterator);
}

TEST(RankIteration, minus_operator)
{
	BoardGame board;
	RankIterator rank_iterator{ board };
	auto& iterator = rank_iterator.begin(board[1]);
	--iterator;
	EXPECT_EQ(iterator->get_value(), 0);
	--iterator;
	EXPECT_FALSE(iterator);
}


TEST(FileIteration, all_operator)
{
	BoardGame board;
	FileIterator file_iterator{ board };
	auto& iterator = file_iterator.begin(board[1]);
	++iterator;
	EXPECT_EQ(iterator->get_value(), 9);
	iterator += 3;
	EXPECT_EQ(iterator->get_value(), 33);
	--iterator;
	EXPECT_EQ(iterator->get_value(), 25);
	iterator += 5;
	EXPECT_FALSE(iterator);
}


TEST(DiagonalIteration, all_operator)
{
	BoardGame board;
	DiagonalIterator diagonal_iterator{ board };
	auto& iterator = diagonal_iterator.begin(board[1]);
	++iterator;
	EXPECT_EQ(iterator->get_value(), 8);
	++iterator;
	EXPECT_FALSE(iterator);
	iterator-=2;
	EXPECT_TRUE(iterator);
	EXPECT_EQ(iterator->get_value(), 1);
}

TEST(AntiDiagonalIteration, all_operator)
{
	BoardGame board;
	AntiDiagonalIterator anti_diagonal_iterator{ board };
	auto& iterator = anti_diagonal_iterator.begin(board[1]);
	++iterator;
	EXPECT_EQ(iterator->get_value(), 10);
	++iterator;
	EXPECT_EQ(iterator->get_value(), 19);
	iterator += 5;
	EXPECT_FALSE(iterator);
	--iterator;
	EXPECT_TRUE(iterator);
	EXPECT_EQ(iterator->get_value(), 55);
}

TEST(Iterator, change_begin_square)
{
	BoardGame board;
	RankIterator rank_iterator{ board };
	auto& it_1 = rank_iterator.begin(board[0]);
	++it_1;
	EXPECT_EQ(it_1->get_value(), 1);
	auto& it_2 = rank_iterator.begin(board[10]);
	++it_2;
	EXPECT_EQ(it_2->get_value(), 11);
}
