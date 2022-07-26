#include <memory>
#include "PieceColor.h"
#include "BoardIterator.h"
#include "BoardGame.h"

void PieceColor::init_valuable_pieces() noexcept
{
	const int8_t init_square_value = this->first_rank_ * NB_COLUMNS;
	auto& square_it = RankIterator(this->board_).begin(this->board_[init_square_value]);
	this->create_piece<Rock>(&*square_it);
	this->create_piece<Knight>(&*++square_it);
	this->create_piece<Bishop>(&*++square_it);
	this->create_piece<Queen>(&*++square_it);
	this->create_piece<King>(&*++square_it);
	this->create_piece<Bishop>(&*++square_it);
	this->create_piece<Knight>(&*++square_it);
	this->create_piece<Rock>(&*++square_it);
}

void PieceColor::init_pawns() noexcept
{
	const int8_t init_square_value = this->second_rank_ * NB_COLUMNS;
	for (auto& square_it = RankIterator(this->board_).begin(this->board_[init_square_value]); 
		square_it; ++square_it)
	{
		this->create_piece<Pawn>(&*square_it);
	}
}

