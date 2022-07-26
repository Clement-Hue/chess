#include <memory>
#include "PieceColor.h"
#include "BoardIterator.h"
#include "BoardGame.h"

void PieceColor::init_valuable_pieces() noexcept
{
	const int8_t init_square_value = this->first_rank_ * NB_COLUMNS;
	auto& square_it = RankIterator(this->board_).begin(this->board_[init_square_value]);
	this->pieces_.emplace_back(
		std::make_unique<Rock>( this->board_, *square_it, *this)
	);
	this->pieces_.emplace_back(
		std::make_unique<Knight>(this->board_, *++square_it, *this)
	);
	this->pieces_.emplace_back(
		std::make_unique<Bishop>(this->board_, *++square_it, *this)
	);
	this->pieces_.emplace_back(
		std::make_unique<Queen>(this->board_, *++square_it, *this)
	);
	this->pieces_.emplace_back(
		std::make_unique<King>( this->board_, *++square_it, *this)
	);
	this->pieces_.emplace_back(
		std::make_unique<Bishop>( this->board_, *++square_it, *this)
	);
	this->pieces_.emplace_back(
		std::make_unique<Knight>( this->board_, *++square_it, *this)
	);
	this->pieces_.emplace_back(
		std::make_unique<Rock>( this->board_, *++square_it, *this)
	);
}

void PieceColor::init_pawns() noexcept
{
	const int8_t init_square_value = this->second_rank_ * NB_COLUMNS;
	for (auto& square_it = RankIterator(this->board_).begin(this->board_[init_square_value]); 
		square_it; ++square_it)
	{
		this->pieces_.emplace_back(
			std::make_unique<Pawn>( this->board_, *square_it, *this)
		);
	}
}
