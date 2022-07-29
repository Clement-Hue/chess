#include "PieceColor.h"
#include "BoardIterator.h"
#include "BoardGame.h"


struct Rank
{
	int8_t first, second;
};

PieceColor::pieces_type static default_pieces(PieceColor& color, BoardGame& board ,const Rank rank) noexcept
{
	PieceColor::pieces_type pieces;
	auto& square_it = RankIterator(board)
	.begin((board)[rank.first*NB_COLUMNS]);
	pieces.emplace_back(std::make_unique<Rock>(&*square_it, &color));
	pieces.emplace_back(std::make_unique<Knight>(&*++square_it, &color));
	pieces.emplace_back(std::make_unique<Bishop>(&*++square_it, &color));
	pieces.emplace_back(std::make_unique<Queen>(&*++square_it, &color));
	pieces.emplace_back(std::make_unique<King>(&*++square_it, &color));
	pieces.emplace_back(std::make_unique<Bishop>(&*++square_it, &color));
	pieces.emplace_back(std::make_unique<Knight>(&*++square_it, &color));
	pieces.emplace_back(std::make_unique<Rock>(&*++square_it, &color));
	for (auto& square_it = RankIterator(board)
		.begin((board)[rank.second * NB_COLUMNS]); 
		square_it; ++square_it)
	{
		pieces.emplace_back(std::make_unique<Pawn>(&*square_it, &color));
	}
	return pieces;
}

void BlackColor::set_default_pieces() noexcept
{
	this->set_pieces(
		default_pieces(*this, *this->board_, { 0,1 })
	);
}

void WhiteColor::set_default_pieces() noexcept
{
	this->set_pieces(
		default_pieces(*this, *this->board_, { NB_ROWS - 1,NB_ROWS - 2 })
	);
}


bool PieceColor::is_turn() const noexcept
{
	return this->board_->get_turn() == *this;
}

void PieceColor::compute_legal_squares() const noexcept
{
	for (const auto& piece: this->pieces_)
	{
		piece->compute_legal_squares();
	}
}

void PieceColor::compute_pseudo_legal_squares() const noexcept
{
	for (const auto& piece: this->pieces_)
	{
		piece->compute_pseudo_legal_squares();
	}
}

void PieceColor::add_piece(std::unique_ptr<Piece> piece) noexcept
{
	piece->set_color(this);
	this->pieces_.emplace_back(std::move(piece)); 
}


void PieceColor::set_pieces(pieces_type pieces) noexcept
{
  this->pieces_ = std::move(pieces); 
  for (const auto& piece: this->pieces_)
  {
	  piece->set_color(this);
  }
}


