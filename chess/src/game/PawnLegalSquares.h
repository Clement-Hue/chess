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
	template <typename Color>
	void add_file_legal_squares(PieceColor& color) const noexcept;
	template <typename Color>
	void add_in_passing_move_if_possible(const PieceColor&) const noexcept;
};

template <typename Color>
void PawnLegalSquares::add_file_legal_squares(PieceColor& color) const noexcept
{
	auto& square_it = FileIterator(color.get_board()).begin(*this->pawn_.get_square());
	const int8_t nb_squares = this->pawn_.is_on_start() ? 2 : 1;
	this->increment_fn<Color>(square_it);
	for (int8_t i = 0;  i<nb_squares && square_it && square_it->is_free() ; ++i, this->increment_fn<Color>(square_it))
	{
		this->pawn_.add_move(*square_it);
	}
}


template <typename Color>
void PawnPseudoLegalSquares::add_takeable_squares(PieceColor& color) const noexcept
{
	this->takeable_squares<Color>(color, [](Pawn& pawn, const BoardIterator& square_it)
		{
			if ( square_it )
			{
				pawn.add_move(*square_it);
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
				pawn.get_legal_move(square_it->get_value()) = nullptr;
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

template <typename Color>
void PawnLegalSquares::add_in_passing_move_if_possible(const PieceColor& color) const noexcept
{
	BoardIterator iterators[] = {
		++RankIterator(color.get_board()).begin(*this->pawn_.get_square()),
		--RankIterator(color.get_board()).begin(*this->pawn_.get_square()),
	};
	for (const auto& rank_it : iterators)
	{
		if (const auto enemy_pawn = dynamic_cast<Pawn*>(rank_it->get_piece())
			;enemy_pawn && enemy_pawn->is_enemy_of(this->pawn_) && enemy_pawn->has_double_moved())
		{
			auto& file_it = FileIterator(color.get_board()).begin(*rank_it);
			this->increment_fn<Color>(file_it);
			this->pawn_.get_legal_move(file_it->get_value()) = std::make_unique<InPassingMove>(*enemy_pawn);
		}
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
