#include "BoardGame.h"
#include "Constants.h"
#include "BoardIterator.h"
#include "PieceColor.h"

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

void BoardGame::set_default_pieces() const noexcept
{
	for (const auto& color: this->colors_)
	{
		color->set_default_pieces();
	}
}

void BoardGame::init_game(const int8_t turn) noexcept
{
	this->turn_ = turn;
	this->compute_legal_moves();
}

void BoardGame::next_turn() noexcept
{
	++this->turn_;
	if (this->turn_ == this->colors_.size())
	{
		this->turn_ = 0;
	}
	this->compute_legal_moves();
}

PieceColor& BoardGame::get_turn() const noexcept
{
	return *this->colors_[this->turn_]; 
}

void BoardGame::compute_legal_moves() const noexcept
{
	for (const auto& color: this->colors_)
	{
		color->clear_legal_moves_states();
	}
	for (const auto& color: this->colors_)
	{
		color->compute_pseudo_legal_moves();
	}
	this->colors_[this->turn_]->compute_legal_moves();
}

