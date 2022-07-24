#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "game/PieceColor.h"

class MockPiece final: public Piece
{
public:
	MockPiece(BoardGame& board, Square& square, std::unique_ptr<PieceColor> color = std::make_unique<WhiteColor>()): Piece(board, square, std::move(color)) {}
	void compute_eligible_squares() noexcept override {}
};
