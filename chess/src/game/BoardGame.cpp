#include "BoardGame.h"
#include "Constants.h"
#include "BoardIterator.h"

static std::vector<Square> create_squares()
{
	std::vector<Square> squares;
	squares.reserve(NB_SQUARES);
	for (int8_t i = 0; i<NB_SQUARES; i++)
	{
		squares.emplace_back(Square{ i });
	}
	return squares;
}

BoardGame::BoardGame(): squares_(create_squares())
{
}


void BoardGame::init_game() const noexcept
{
	for (const auto& color: this->colors_)
	{
		color->init_pawns();
		color->init_valuable_pieces();
	}
	this->compute_legal_squares();
}


void BoardGame::next_turn() noexcept
{
	++this->turn_;
	if (this->turn_ == this->colors_.size())
	{
		this->turn_ = 0;
	}
	this->compute_legal_squares();
}

PieceColor& BoardGame::get_turn() const noexcept
{
	return *this->colors_[this->turn_]; 
}

void BoardGame::compute_legal_squares() const noexcept
{
	for (const auto& color: this->colors_)
	{
		color->compute_pseudo_legal_squares();
	}
	this->colors_[this->turn_]->compute_legal_squares();
}

