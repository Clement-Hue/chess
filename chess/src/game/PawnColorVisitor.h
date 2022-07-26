#pragma once
#include "PieceColor.h"
#include "Piece.h"

class PawnColorVisitor: public  ColorVisitor
{
public:
	PawnColorVisitor(Pawn& pawn): pawn_(pawn) {}
	using increment_fn_type = void(*)(BoardIterator&);
protected:
	using takeable_squares_fn_type = void(*)(Pawn&, const BoardIterator&);
	template <typename Color>
	void increment_fn(BoardIterator&) const noexcept = delete;
	template <typename Color>
	void takeable_squares(PieceColor&,takeable_squares_fn_type) const noexcept;
	Pawn& pawn_;
};


class PawnPseudoLegalSquares final: public PawnColorVisitor
{
public:
	PawnPseudoLegalSquares(Pawn& pawn): PawnColorVisitor(pawn) {}
	void visit(BlackColor&) const override;
	void visit(WhiteColor&) const override;
private:
	template <typename Color>
	void add_file_eligible_squares(PieceColor& color) const noexcept;
	template <typename Color>
	void add_takeable_squares(PieceColor& color) const noexcept;
};

class PawnLegalSquares final: public PawnColorVisitor
{
public:
	PawnLegalSquares(Pawn& pawn): PawnColorVisitor(pawn) {}
	void visit(BlackColor& color) const override;
	void visit(WhiteColor& color) const override;
private:
	template <typename Color>
	void remove_not_legal_takeable_squares(PieceColor& color) const noexcept;
};

template <typename Color>
void PawnPseudoLegalSquares::add_file_eligible_squares(PieceColor& color) const noexcept
{
	auto& square_it = FileIterator(color.get_board()).begin(*this->pawn_.get_square());
	if (this->increment_fn<Color>(square_it); square_it && square_it->is_free())
	{
		this->pawn_.get_legal_square(square_it->get_value()) = &*square_it;
		if (this->pawn_.get_square()->get_rank() == this->pawn_.get_color().get_second_rank())
		{
			if (this->increment_fn<Color>(square_it); square_it && square_it->is_free())
			{
				this->pawn_.get_legal_square(square_it->get_value()) = &*square_it;
			}
		}
	}
}


template <typename Color>
void PawnPseudoLegalSquares::add_takeable_squares(PieceColor& color) const noexcept
{
	this->takeable_squares<Color>(color, [](Pawn& pawn, const BoardIterator& square_it)
		{
			if ( square_it )
			{
				pawn.get_legal_square(square_it->get_value()) = &*square_it;
			}
		});
}

template <typename Color>
void PawnLegalSquares::remove_not_legal_takeable_squares(PieceColor& color) const noexcept
{
	this->takeable_squares<Color>(color, [](Pawn& pawn, const BoardIterator& square_it)
		{
			if ( square_it && !square_it->has_enemy_piece_of(pawn) )
			{
				pawn.get_legal_square(square_it->get_value()) = nullptr;
			}
		});
}

template<typename Color>
void PawnColorVisitor::takeable_squares(PieceColor& color,const takeable_squares_fn_type takeable_square_fn) const noexcept
{
	BoardIterator iterators[2] = { DiagonalIterator(color.get_board()),  AntiDiagonalIterator(color.get_board()) };
	for (auto& square_it : iterators)
	{
		square_it.begin(*this->pawn_.get_square());
		this->increment_fn<Color>(square_it);
		takeable_square_fn(this->pawn_, square_it);
	}
}

template <>
inline void PawnColorVisitor::increment_fn<WhiteColor>(BoardIterator& it) const noexcept
{
	--it;
}


template <>
inline void PawnColorVisitor::increment_fn<BlackColor>(BoardIterator& it) const noexcept
{
	++it;
}
