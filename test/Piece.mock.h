#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"

class MockPiece final: public Piece
{
public:
	MockPiece(BoardGame& board, Square& square, const PieceColor color = PieceColor::white): Piece(board, square, color) {}
	void compute_eligible_squares() noexcept override {}
};
