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

std::vector<Square*> Rock::available_square() const noexcept
{
	std::vector<Square*> squares;
	const uint8_t column = this->square_->get_value() % NB_SQUARES_BY_ROW;
	const uint8_t row = this->square_->get_value() / NB_SQUARES_BY_ROW;
	for (int8_t i = this->square_->get_value() + NB_SQUARES_BY_ROW; i<NB_SQUARES; i+=NB_SQUARES_BY_ROW )
	{
		if (!this->board_[i].is_free())
		{
			if (this->board_[i].has_enemy_piece_of(*this))
			{
				squares.emplace_back(&this->board_[i]);
			}
			break;
		}
		squares.emplace_back(&this->board_[i]);
	}
	for (int8_t i = this->square_->get_value() - NB_SQUARES_BY_ROW; i>= 0; i-=NB_SQUARES_BY_ROW )
	{
		if (!this->board_[i].is_free())
		{
			if (this->board_[i].has_enemy_piece_of(*this))
			{
				squares.emplace_back(&this->board_[i]);
			}
			break;
		}
		squares.emplace_back(&this->board_[i]);
	}
	for (int8_t i = this->square_->get_value() - 1;  this->square_->is_same_row(i) ; --i)
	{
		if (!this->board_[i].is_free())
		{
			if (this->board_[i].has_enemy_piece_of(*this))
			{
				squares.emplace_back(&this->board_[i]);
			}
			break;
		}
		squares.emplace_back(&this->board_[i]);
	}
	for (int8_t i = this->square_->get_value() + 1;  this->square_->is_same_row(i) ; ++i)
	{
		if (!this->board_[i].is_free())
		{
			if (this->board_[i].has_enemy_piece_of(*this))
			{
				squares.emplace_back(&this->board_[i]);
			}
			break;
		}
		squares.emplace_back(&this->board_[i]);
	}
	return squares;
}
