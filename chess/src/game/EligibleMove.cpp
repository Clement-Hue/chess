#include "EligibleMove.h"

#include "BoardGame.h"

void EligibleMove::add_eligible_squares(const int8_t offset ) const noexcept
{
	for (int8_t i = this->piece_.get_square()->get_value() + offset;
		this->board_.has_square_value(i) && this->is_eligible_square(this->board_[i])
		; i += offset)
	{
		if (!this->board_[i].is_free())
		{
			if (this->board_[i].has_enemy_piece_of(this->piece_))
			{
				this->piece_.get_eligible_square(i) =  &this->board_[i];
				this->check_pinning(*this->board_[i].get_piece(), offset);
			}
			break;
		}
		this->piece_.get_eligible_square(i) =  &this->board_[i];
	}
}

void EligibleMove::check_pinning(Piece& piece, const int8_t offset ) const noexcept
{
	for (int8_t i = piece.get_square()->get_value() + offset;
		this->board_.has_square_value(i) && this->is_eligible_square(this->board_[i])
		&& !this->board_[i].has_friend_piece_of(this->piece_)
		; i += offset)
	{
		if (this->board_[i].has_enemy_piece_of(this->piece_))
		{
			if (dynamic_cast<King*>( this->board_[i].get_piece()))
			{
				piece.set_pinning_filter(this->pinning_filter_);
			}
			return;
		}
	}
}

void EligibleMove::operator()() const noexcept
{
	this->add_eligible_squares(this->offset_);
	this->add_eligible_squares(-this->offset_);
}

