#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "game/PieceColor.h"

class MockPiece final: public Piece
{
public:
	MockPiece(BoardGame& board, Square& square, PieceColor& color): Piece(board, square, color) {}
	void compute_pseudo_legal_squares() noexcept override {}
};
