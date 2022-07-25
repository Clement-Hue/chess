#include "Piece.h"
#include "BoardGame.h"
#include "BoardIterator.h"
#include "EligibleSquares.h"
#include "PieceColor.h"


Piece::Piece(BoardGame& board, Square& square, std::unique_ptr<PieceColor> color):
board_(board), square_(&square), color_(std::move(color))	
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

void Rock::compute_eligible_squares() noexcept
{
	linear_eligible_squares::add_rank_squares(*this, this->board_);
	linear_eligible_squares::add_file_squares(*this, this->board_);
}

void Bishop::compute_eligible_squares() noexcept
{
	linear_eligible_squares::add_diagonal_squares(*this, this->board_);
	linear_eligible_squares::add_anti_diagonal_squares(*this, this->board_);
}

void Queen::compute_eligible_squares() noexcept
{
	linear_eligible_squares::add_rank_squares(*this, this->board_);
	linear_eligible_squares::add_file_squares(*this, this->board_);
	linear_eligible_squares::add_diagonal_squares(*this, this->board_);
	linear_eligible_squares::add_anti_diagonal_squares(*this, this->board_);
}

void King::compute_eligible_squares() noexcept
{
	BoardIterator iterators[8] = {
		++RankIterator(this->board_).begin(*this->square_), --RankIterator(this->board_).begin(*this->square_),
		++FileIterator(this->board_).begin(*this->square_), --FileIterator(this->board_).begin(*this->square_),
		++DiagonalIterator(this->board_).begin(*this->square_), --DiagonalIterator(this->board_).begin(*this->square_),
		++AntiDiagonalIterator(this->board_).begin(*this->square_), --AntiDiagonalIterator(this->board_).begin (*this->square_)
	};
	for (const auto& square_it: iterators)
	{
		if ( square_it && !square_it->has_friend_piece_of(*this) )
		{
			this->eligible_squares_[square_it->get_value()] = &*square_it;
		}
	}
}

void Knight::compute_eligible_squares() noexcept
{
	this->add_eligible_squares<FileIterator, RankIterator>();
	this->add_eligible_squares<RankIterator, FileIterator>();
}


void Pawn::compute_eligible_squares() noexcept
{
	this->get_color().accept(PawnEligibleSquares(*this, this->board_));
}
