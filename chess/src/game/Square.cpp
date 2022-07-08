#include "Square.h"
#include "Piece.h"

bool Square::has_enemy_piece_of(const Piece& piece) const noexcept
{
	if (this->piece_ == nullptr) return false;
	return this->piece_->get_color() != piece.get_color();
}
