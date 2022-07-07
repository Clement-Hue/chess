#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"

class MockPiece final: public Piece
{
public:
	MockPiece(BoardGame& board, Square& square): Piece(board, square) {}
	std::vector<Square*> available_square() const noexcept override { return {}; }
};

TEST(BoardGameTest, ConstructSquares)
{
	BoardGame board;
	for (uint8_t i = 0; i< 64 ; ++i)
	{
		EXPECT_EQ(board[i].value, i);
	}
}

TEST(PieceTest, LinkPieceAndSquare)
{
	BoardGame board;
	const MockPiece piece{ board, board[2] };
	EXPECT_EQ(board[2].piece, &piece) << "Piece are not the same";
}

TEST(PieceTest, LinkPieceAndSquareWhenMoving)
{
	BoardGame board;
	MockPiece piece{ board, board[2] };
	piece.move(board[4]);
	EXPECT_EQ(board[4].piece, &piece) << "Piece hasn't moved";
	EXPECT_NE(board[2].piece, &piece) << "Piece still present on old square";
}

TEST(MoveTest, RockMove)
{
	BoardGame board;
	const std::vector<Square> expected_moves = {
		{0}, {1}, {2}, {4}, {5},{6},{7},
		{11}, {19}, {27}, {35}, {43}, {51}, {59}, 	};
	const Rock rock{ board, board[3] };
	const auto rock_moves = rock.available_square();
	for (uint8_t i = 0; i<expected_moves.size(); ++i)
	{
		EXPECT_EQ(expected_moves[i], *rock_moves[i]) << "Different at " << +i << 
			" expected " << +expected_moves[i].value << " received " << 
			+rock_moves[i]->value;
	}
}

TEST(MoveTest, RockMoveWithSquaresTaken)
{
	BoardGame board;
	MockPiece piece{board, board[10]};
}
