#include "PieceColor.h"
#include "BoardIterator.h"
#include "BoardGame.h"

void PieceColor::set_default_pieces() noexcept
{
	auto& first_rank_it = RankIterator(this->board_).begin(this->board_[this->rank_.first * NB_COLUMNS]);
	this->add_piece<Rock>(*first_rank_it);
	this->add_piece<Knight>(*++first_rank_it);
	this->add_piece<Bishop>(*++first_rank_it);
	this->add_piece<Queen>(*++first_rank_it);
	this->add_piece<King>(*++first_rank_it);
	this->add_piece<Bishop>(*++first_rank_it);
	this->add_piece<Knight>(*++first_rank_it);
	this->add_piece<Rock>(*++first_rank_it);
	for (auto& second_rank_it = RankIterator(this->board_).begin(this->board_[this->rank_.second * NB_COLUMNS]); 
		second_rank_it; ++second_rank_it)
	{
		this->add_piece<Pawn>(*second_rank_it);
	}
}

bool PieceColor::is_square_attacked(const Square& square) const noexcept
{
	for (const auto& color: this->board_.get_colors())
	{
		if (*color == *this) continue;
		for (const auto& piece: color->get_pieces())
		{
			if (piece->get_legal_move(square.get_value())) return true;
		}
	}
	return false;
}

void PieceColor::remove_piece(Piece& piece) noexcept
{
	if (const auto pawn_it = std::find_if(this->pieces_.begin(), this->pieces_.end(),
		[&piece](const std::unique_ptr<Piece>& ptr) { return &*ptr == &piece; }
		); pawn_it  != this->pieces_.end())
	{
		this->pieces_.erase(pawn_it);
	}
}

King* PieceColor::get_king() const noexcept
{
	for (const auto& piece: this->pieces_)
	{
		if (const auto& king = dynamic_cast<King*>(&*piece))
		{
			return king;
		}
	}
	return nullptr;
}



bool PieceColor::is_turn() const noexcept
{
	return this->board_.get_turn() == *this;
}

void PieceColor::compute_legal_moves() const noexcept
{
	for (const auto& piece: this->pieces_)
	{
		if (!piece->is_in_board()) continue;
		piece->compute_legal_moves();
	}
}

void PieceColor::clear_legal_moves_states() const noexcept
{
	for (const auto& piece: this->pieces_)
	{
		piece->clear_legal_moves_states();
	}
}


void PieceColor::remove_illegal_moves_of_enemy(PieceColor& color) const noexcept
{
	for (const auto& piece: this->pieces_)
	{
		if (piece->is_in_board())
		{
			piece->remove_illegal_moves_of_enemy(color);
		}
	}
}

void PieceColor::add_piece_observer(std::unique_ptr<PieceObserver> obs) noexcept
{
	this->piece_observers_.emplace_back(std::move(obs));
}

