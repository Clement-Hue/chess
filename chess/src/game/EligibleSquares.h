#pragma once
#include "Common.h"
#include "PieceColor.h"
#include "Piece.h"
#include "Square.h"
#include "BoardIterator.h"

class BoardGame;
class Piece;

namespace linear_eligible_squares
{
	CHESS_API void add_rank_squares(Piece& piece, BoardGame& board);
	CHESS_API void add_file_squares(Piece& piece, BoardGame& board);
	CHESS_API void add_diagonal_squares(Piece& piece, BoardGame& board);
	CHESS_API void add_anti_diagonal_squares(Piece& piece, BoardGame& board);
}

class CHESS_API PawnEligibleSquares final: public ColorVisitor
{
public:
	PawnEligibleSquares(Pawn& pawn, BoardGame& board): ColorVisitor(),pawn_(pawn), board_(board) {}
	void visit(BlackColor&) const override;
	void visit(WhiteColor&) const override;
private:
	using increment_fn_type = void(*)(BoardIterator&);
	template <typename Color>
	void add_file_eligible_squares(increment_fn_type increment_fn) const noexcept;
	Pawn& pawn_;
	BoardGame& board_;
};

template <typename Color>
void PawnEligibleSquares::add_file_eligible_squares(const increment_fn_type increment_fn) const noexcept
{
	auto square_it = FileIterator(this->board_).begin(*this->pawn_.get_square());
	if (increment_fn(square_it); square_it)
	{
		this->pawn_.get_eligible_square(square_it->get_value()) = &*square_it;
	}
	if (this->pawn_.get_square()->get_rank() == Color::second_rank)
	{
		if (increment_fn(square_it); square_it)
		{
			this->pawn_.get_eligible_square(square_it->get_value()) = &*square_it;
		}
	}
}

