#include "Square.h"
#include "Piece.h"
#include <cstdlib>

bool Square::has_enemy_piece_of(const Piece& piece) const noexcept
{
	if (this->piece_ == nullptr) return false;
	return this->piece_->get_color() != piece.get_color();
}

bool Square::has_friend_piece_of(const Piece& piece) const noexcept
{
	if (this->piece_ == nullptr) return false;
	return this->piece_->get_color() == piece.get_color();
}

bool Square::is_same_diagonal(const Square& square) const noexcept
{
	return abs(square.get_file() - this->get_file()) == abs(square.get_rank() - this->get_rank());
}
