#include "Square.h"
#include "Piece.h"

static int8_t get_file_of_value(const int8_t value)
{
	 return value % NB_SQUARES_BY_ROW; 
}

static int8_t get_rank_of_value(const int8_t value)
{
	return value / NB_SQUARES_BY_ROW; 
}

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

int8_t Square::get_rank() const noexcept
{
	return get_rank_of_value(this->value_);
}

int8_t Square::get_file() const noexcept
{
	return get_file_of_value(this->value_);
}

bool Square::is_same_diagonal(const Square& square) const noexcept
{
	return this->is_same_diagonal(square.get_value());
}

bool Square::is_same_diagonal(const int8_t value) const noexcept
{
	return get_file_of_value(value) - this->get_file() == -(get_rank_of_value(value) - this->get_rank());
}

bool Square::is_same_anti_diagonal(const Square& square) const noexcept
{
	return this->is_same_anti_diagonal(square.get_value());
}

bool Square::is_same_anti_diagonal(const int8_t value) const noexcept
{
	return get_file_of_value(value)  - this->get_file() == get_rank_of_value(value) - this->get_rank();
}
