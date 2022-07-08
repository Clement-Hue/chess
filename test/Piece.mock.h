#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"

class MockPiece final: public Piece
{
public:
	MockPiece(BoardGame& board, Square& square, const Color color = Color::white): Piece(board, square, color) {}
	std::vector<Square*> eligible_squares() const noexcept override { return {}; }
};
