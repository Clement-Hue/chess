#include "EligibleMove.h"
#include "BoardGame.h"

void EligibleMove::add_eligible_squares(const increment_fn_type increment_fn)  noexcept
{
	for (auto& square_iterator = this->iterator_.begin(*this->piece_.get_square());
		square_iterator ; increment_fn(square_iterator))
	{
		if (&*square_iterator == this->piece_.get_square()) continue;
		if (!square_iterator->is_free())
		{
			if (square_iterator->has_enemy_piece_of(this->piece_))
			{
				this->piece_.get_eligible_square(square_iterator->get_value()) = &*square_iterator;
				this->check_pinning(*square_iterator->get_piece(), increment_fn);
			}
			break;
		}
		this->piece_.get_eligible_square(square_iterator->get_value()) = &*square_iterator;
	}
}

void EligibleMove::check_pinning(Piece& piece, const increment_fn_type increment_fn ) noexcept
{
	for (auto& square_iterator = this->iterator_.begin(*piece.get_square());
		square_iterator && !square_iterator->has_friend_piece_of(this->piece_)
		; increment_fn(square_iterator))
	{
		if (&*square_iterator == piece.get_square()) continue;
		if (square_iterator->has_enemy_piece_of(this->piece_))
		{
			if (dynamic_cast<King*>( square_iterator->get_piece()))
			{
				piece.set_pinning_filter(this->pinning_filter_);
			}
			return;
		}
	}
}

void EligibleMove::operator()() noexcept
{
	this->add_eligible_squares([](BoardIterator& it) {++it; });
	this->add_eligible_squares([](BoardIterator& it) {--it; });
}

