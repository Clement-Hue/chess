#include "LinearEligibleMove.h"
#include "BoardGame.h"

void LinearEligibleMove::add_eligible_squares(const increment_fn_type increment_fn)  noexcept
{
	for (auto& square_it = this->iterator_.begin(*this->piece_.get_square());
		square_it ; increment_fn(square_it))
	{
		if (&*square_it == this->piece_.get_square()) continue;
		if (!square_it->is_free())
		{
			if (square_it->has_enemy_piece_of(this->piece_))
			{
				this->piece_.get_eligible_square(square_it->get_value()) = &*square_it;
				this->check_pinning(*square_it->get_piece(), increment_fn);
			}
			break;
		}
		this->piece_.get_eligible_square(square_it->get_value()) = &*square_it;
	}
}

void LinearEligibleMove::check_pinning(Piece& piece, const increment_fn_type increment_fn ) noexcept
{
	for (auto& square_it= this->iterator_.begin(*piece.get_square());
		square_it && !square_it->has_friend_piece_of(this->piece_)
		; increment_fn(square_it))
	{
		if (&*square_it == piece.get_square()) continue;
		if (square_it->has_enemy_piece_of(this->piece_))
		{
			if (dynamic_cast<King*>( square_it->get_piece()))
			{
				piece.set_pinning_filter(this->pinning_filter_);
			}
			return;
		}
	}
}

void LinearEligibleMove::operator()() noexcept
{
	this->add_eligible_squares([](BoardIterator& it) {++it; });
	this->add_eligible_squares([](BoardIterator& it) {--it; });
}

