#include "BoardIterator.h"
#include "Square.h"
#include "BoardGame.h"

BoardIterator& BoardIterator::begin(const Square& square) noexcept
{
	this->square_ = &square; 
	this->square_value_ = square.get_value();
	return *this;
}

BoardIterator::operator bool() const noexcept
{
	return this->board_.has_square_value(this->square_value_) &&
		(this->square_->*this->predicate_)(this->square_value_);
}

Square& BoardIterator::operator*() const noexcept
{
	return this->board_[this->square_value_];
}
