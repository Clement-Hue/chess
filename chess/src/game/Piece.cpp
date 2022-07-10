#include "Piece.h"
#include "BoardGame.h"
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


void Piece::add_eligible_file_squares(std::array<Square*, NB_SQUARES>& squares) const noexcept
{
	for (int8_t i = this->square_->get_value(); 
		this->is_eligible_square(squares, i)
		; i += NB_SQUARES_BY_ROW);
	for (int8_t i = this->square_->get_value();
		this->is_eligible_square(squares, i)
		; i -= NB_SQUARES_BY_ROW);
}

void Piece::add_eligible_row_squares(std::array<Square*, NB_SQUARES>& squares) const noexcept
{
	for (int8_t i = this->square_->get_value() - 1; 
		this->square_->is_same_rank(i) && this->is_eligible_square(squares, i)
		; --i);
	for (int8_t i = this->square_->get_value() + 1; 
		this->square_->is_same_rank(i) && this->is_eligible_square(squares, i)
		; ++i);
}

void Piece::add_eligible_diagonals(std::array<Square*, NB_SQUARES>& squares) const noexcept
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
bool Piece::is_eligible_square(std::array<Square*, NB_SQUARES>& squares, const int8_t square_value) const noexcept
{
	if (this->square_->get_value() == square_value) return true;
	if (square_value >= NB_SQUARES || square_value < 0) return false;
	if (!this->board_[square_value].is_free())
	{
		if (this->board_[square_value].has_enemy_piece_of(*this))
		{
			squares[square_value] =  &this->board_[square_value];
		}
		return false;
	}
	squares[square_value] =  &this->board_[square_value];
	return true;
}


std::array<Square*, NB_SQUARES> Rock::get_eligible_squares() const noexcept
{
	std::array<Square*, NB_SQUARES> squares{};
	this->add_eligible_file_squares(squares);
	this->add_eligible_row_squares(squares);
	return squares;
}

std::array<Square*, NB_SQUARES> Bishop::get_eligible_squares() const noexcept
{
	std::array<Square*, NB_SQUARES> squares{};
	this->add_eligible_diagonals(squares);
	return squares;
}

std::array<Square*, NB_SQUARES> Queen::get_eligible_squares() const noexcept
{
	std::array<Square*, NB_SQUARES> squares{};
	this->add_eligible_file_squares(squares);
	this->add_eligible_row_squares(squares);
	this->add_eligible_diagonals(squares);
	return squares;
}

std::array<Square*, NB_SQUARES> King::get_eligible_squares() const noexcept
{
	std::array<Square*, NB_SQUARES> squares{};
	constexpr uint8_t offsets[4] = { 1,NB_SQUARES_BY_ROW -1,NB_SQUARES_BY_ROW, NB_SQUARES_BY_ROW + 1};
	for (const auto offset : offsets)
	{
		this->is_eligible_square(squares, this->square_->get_value() + offset);
		this->is_eligible_square(squares, this->square_->get_value() - offset);
	}
	return squares;
}

std::array<Square*, NB_SQUARES> Knight::get_eligible_squares() const noexcept
{
	return std::array<Square*, NB_SQUARES>();
}

std::array<Square*, NB_SQUARES> Pawn::get_eligible_squares() const noexcept
{
	return std::array<Square*, NB_SQUARES>();
}
