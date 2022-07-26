#include "Piece.h"
#include "BoardGame.h"
#include "BoardIterator.h"
#include "PseudoLegalSquares.h"
#include "PieceColor.h"
#include "PawnColorVisitor.h"


Piece::Piece(BoardGame& board, Square& square, PieceColor& color):
board_(board), square_(&square), color_(color)
{
	this->square_->set_piece(*this);
}

bool Piece::is_enemy_of(const Piece& piece) const noexcept
{
	return this->get_color() != piece.get_color(); 
}

bool Piece::is_friend_of(const Piece& piece) const noexcept
{
	return !this->is_enemy_of(piece);
}

void Piece::compute_legal_squares() noexcept
{
	this->filter_legal_squares_if_pinned();
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

void Rock::compute_pseudo_legal_squares() noexcept
{
	linear_pseudo_legal_squares::add_rank_squares(*this, this->board_);
	linear_pseudo_legal_squares::add_file_squares(*this, this->board_);
}

void Bishop::compute_pseudo_legal_squares() noexcept
{
	linear_pseudo_legal_squares::add_diagonal_squares(*this, this->board_);
	linear_pseudo_legal_squares::add_anti_diagonal_squares(*this, this->board_);
}

void Queen::compute_pseudo_legal_squares() noexcept
{
	linear_pseudo_legal_squares::add_rank_squares(*this, this->board_);
	linear_pseudo_legal_squares::add_file_squares(*this, this->board_);
	linear_pseudo_legal_squares::add_diagonal_squares(*this, this->board_);
	linear_pseudo_legal_squares::add_anti_diagonal_squares(*this, this->board_);
}

void King::compute_pseudo_legal_squares() noexcept
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
			this->legal_squares[square_it->get_value()] = &*square_it;
		}
	}
}

void Knight::compute_pseudo_legal_squares() noexcept
{
	this->add_eligible_squares<FileIterator, RankIterator>();
	this->add_eligible_squares<RankIterator, FileIterator>();
}

void Pawn::compute_pseudo_legal_squares() noexcept
{
	this->get_color().accept(PawnPseudoLegalSquares(*this, this->board_));
}

void Pawn::compute_legal_squares() noexcept 
{
	Piece::compute_legal_squares();
	this->get_color().accept(PawnLegalTakeableSquares(*this, this->board_));
}
