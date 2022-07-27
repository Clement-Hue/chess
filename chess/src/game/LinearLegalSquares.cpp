#include "LinearLegalSquares.h"
#include "BoardGame.h"

class LinearPseudoLegalSquares
{
	using increment_fn_type = void (*)(BoardIterator&);
public:
	LinearPseudoLegalSquares(Piece& piece, const BoardIterator iterator , const Piece::pinning_filter_type pinning_fn ):
	piece_(piece), iterator_(iterator), pinning_filter_(pinning_fn){}
	void operator()() noexcept;
private:
	void add_pseudo_legal_squares(increment_fn_type increment_fn)   noexcept;
	void check_pinning( Piece& piece, increment_fn_type increment_fn ) noexcept;
	Piece& piece_;
	BoardIterator iterator_;
	Piece::pinning_filter_type pinning_filter_;
};

void LinearPseudoLegalSquares::add_pseudo_legal_squares(const increment_fn_type increment_fn)  noexcept
{
	for (auto& square_it = this->iterator_.begin(*this->piece_.get_square());
		square_it ; increment_fn(square_it))
	{
		if (&*square_it == this->piece_.get_square()) continue;
		if (!square_it->is_free())
		{
			if (square_it->has_enemy_piece_of(this->piece_))
			{
				this->piece_.get_legal_square(square_it->get_value()) = &*square_it;
				this->check_pinning(*square_it->get_piece(), increment_fn);
			}
			return;
		}
		this->piece_.get_legal_square(square_it->get_value()) = &*square_it;
	}
}

void LinearPseudoLegalSquares::check_pinning(Piece& piece, const increment_fn_type increment_fn ) noexcept
{
	for (auto& square_it= this->iterator_.begin(*piece.get_square());
		square_it && !square_it->has_friend_piece_of(this->piece_)
		; increment_fn(square_it))
	{
		if (&*square_it == piece.get_square()) continue;
		if (square_it->has_enemy_piece_of(this->piece_))
		{
			if (dynamic_cast<King*>( square_it->get_piece()))
			{
				piece.set_pinning_filter(this->pinning_filter_);
			}
			return;
		}
	}
}

void LinearPseudoLegalSquares::operator()() noexcept
{
	this->add_pseudo_legal_squares([](BoardIterator& it) {++it; });
	this->add_pseudo_legal_squares([](BoardIterator& it) {--it; });
}

using square_fn_type = bool (Square::*) (const Square&) const ;
static void base_filter(Piece& piece,  const square_fn_type predicate )
{
	auto& legal_squares = piece.get_legal_squares();
	for (int8_t i =0 ; i < legal_squares.size(); ++i)
	{
		if (!legal_squares[i] || (piece.get_square()->*predicate)(*legal_squares[i])) continue;
		piece.get_legal_square(i) = nullptr;
	}
}

void linear_pseudo_legal_squares::add_rank_squares(Piece& piece, BoardGame& board)
{
	LinearPseudoLegalSquares(piece, RankIterator(board), [](Piece& p)
	{
		base_filter(p, &Square::is_same_rank);
	})();
}

void linear_pseudo_legal_squares::add_file_squares(Piece& piece, BoardGame& board)
{
	LinearPseudoLegalSquares(piece, FileIterator(board), [](Piece& p)
	{
		base_filter(p, &Square::is_same_file);
	})();
}

void linear_pseudo_legal_squares::add_diagonal_squares(Piece& piece, BoardGame& board)
{
	LinearPseudoLegalSquares(piece, DiagonalIterator(board), [](Piece& p)
	{
		base_filter(p, &Square::is_same_diagonal);
	})();
}

void linear_pseudo_legal_squares::add_anti_diagonal_squares(Piece& piece, BoardGame& board)
{
	LinearPseudoLegalSquares(piece, AntiDiagonalIterator(board), [](Piece& p)
	{
		base_filter(p, &Square::is_same_anti_diagonal);
	})();
}

