#include "Piece.h"
#include "Constants.h"


Piece::Piece(BoardGame& board, Square& square, const PieceColor color): board_(board), square_(&square),
	color_(color)	
{
	this->square_->set_piece(*this);
}

void Piece::move(Square& square) noexcept
{
	const auto piece_on_square = square.get_piece();
	if (piece_on_square && piece_on_square->is_friend_of(*this)) return;
	if (piece_on_square && piece_on_square->is_enemy_of(*this))
	{
		piece_on_square->remove_square();
	}
	this->square_->remove_piece();
	this->square_ = &square;
	this->square_->set_piece(*this);
}


void Piece::add_eligible_file_squares(std::vector<Square*>& squares) const noexcept
{
	for (int8_t i = this->square_->get_value(); 
		this->is_eligible_square(squares, i)
		; i += NB_SQUARES_BY_ROW);
	for (int8_t i = this->square_->get_value();
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

void Piece::add_eligible_diagonals(std::vector<Square*>& squares) const noexcept
{
	for (int8_t i = this->square_->get_value(); 
		this->board_[i].get_file() >= this->square_->get_file() && this->is_eligible_square(squares, i)
		; i += NB_SQUARES_BY_ROW + 1);
	for (int8_t i = this->square_->get_value(); 
		this->board_[i].get_file() <= this->square_->get_file() && this->is_eligible_square(squares, i)
		; i += NB_SQUARES_BY_ROW - 1);
	for (int8_t i = this->square_->get_value(); 
		this->board_[i].get_file() <= this->square_->get_file() && this->is_eligible_square(squares, i)
		; i -= NB_SQUARES_BY_ROW + 1);
	for (int8_t i = this->square_->get_value(); 
		this->board_[i].get_file() >= this->square_->get_file() && this->is_eligible_square(squares, i)
		; i -= NB_SQUARES_BY_ROW - 1);
}

/**
 * Predicate with side effect.
 * Add the square to the vector if the square is eligible
 */
bool Piece::is_eligible_square(std::vector<Square*>& squares, const int8_t square_value) const noexcept
{
	if (this->square_->get_value() == square_value) return true;
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


std::vector<Square*> Rock::get_eligible_squares() const noexcept
{
	std::vector<Square*> squares;
	this->add_eligible_file_squares(squares);
	this->add_eligible_row_squares(squares);
	return squares;
}

std::vector<Square*> Bishop::get_eligible_squares() const noexcept
{
	std::vector<Square*> squares;
	this->add_eligible_diagonals(squares);
	return squares;
}

std::vector<Square*> Queen::get_eligible_squares() const noexcept
{
	std::vector<Square*> squares;
	this->add_eligible_file_squares(squares);
	this->add_eligible_row_squares(squares);
	this->add_eligible_diagonals(squares);
	return squares;
}
