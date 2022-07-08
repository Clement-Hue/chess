#include "Piece.h"
#include "Constants.h"


Piece::Piece(BoardGame& board, Square& square, const Color color): board_(board), square_(&square),
	color_(color)	
{
	this->square_->set_piece(*this);
}

void Piece::move(Square& square) noexcept
{
	this->square_->remove_piece();
	this->square_ = &square;
	this->square_->set_piece(*this);
}


std::vector<Square*> Rock::eligible_squares() const noexcept
{
	std::vector<Square*> squares;
	this->add_eligible_file_squares(squares);
	this->add_eligible_row_squares(squares);
	return squares;
}

void Piece::add_eligible_file_squares(std::vector<Square*>& squares) const noexcept
{
	for (int8_t i = this->square_->get_value() + NB_SQUARES_BY_ROW;
		this->is_eligible_square(squares, i)
		; i += NB_SQUARES_BY_ROW);
	for (int8_t i = this->square_->get_value() - NB_SQUARES_BY_ROW;
		this->is_eligible_square(squares, i)
		; i -= NB_SQUARES_BY_ROW);
}

void Piece::add_eligible_row_squares(std::vector<Square*>& squares) const noexcept
{
	for (int8_t i = this->square_->get_value() - 1; 
		this->square_->is_same_rank(i) && this->is_eligible_square(squares, i)
		; --i);
	for (int8_t i = this->square_->get_value() + 1; 
		this->square_->is_same_rank(i) && this->is_eligible_square(squares, i)
		; ++i);
}

/**
 * Predicate with side effect.
 * Add the square to the vector if the square is eligible
 */
bool Piece::is_eligible_square(std::vector<Square*>& squares, const int8_t square_value) const noexcept
{
	if (square_value > NB_SQUARES || square_value < 0) return false;
	if (!this->board_[square_value].is_free())
	{
		if (this->board_[square_value].has_enemy_piece_of(*this))
		{
			squares.emplace_back(&this->board_[square_value]);
		}
		return false;
	}
	squares.emplace_back(&this->board_[square_value]);
	return true;
}
