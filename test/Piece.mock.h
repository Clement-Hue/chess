#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "game/PieceColor.h"

class MockPiece final: public Piece
{
public:
	MockPiece(Square* square, PieceColor& color): Piece( square, color) {}
	void compute_pseudo_legal_moves() noexcept override {}
	void accept(const PieceVisitor& visitor) override {}
	bool is_on_start() const noexcept override { return false; }
};
