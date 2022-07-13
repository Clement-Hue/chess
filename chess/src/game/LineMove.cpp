#include "LineMove.h"

#include "BoardGame.h"

void LineMove::add_eligible_squares(e_squares_type& squares) const noexcept
{
	for (int8_t i = this->piece_.get_square()->get_value() + this->get_offset();
		this->board_.has_square_value(i) && this->is_eligible_square(this->board_[i])
		; i += this->get_offset())
	{
		if (!this->board_[i].is_free())
		{
			if (this->board_[i].has_enemy_piece_of(this->piece_))
			{
				squares[i] =  &this->board_[i];
				this->check_pinning(*this->board_[i].get_piece());
			}
			break;
		}
		squares[i] =  &this->board_[i];
	}
}

void LineMove::check_pinning(const Piece& square) const noexcept
{
}
