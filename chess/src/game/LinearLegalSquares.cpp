#include "LinearLegalSquares.h"
#include "BoardGame.h"
#include "Move.h"

class LinearLegalMoves
{
	using increment_fn_type = void (*)(BoardIterator&);
public:
	LinearLegalMoves(Piece& piece, const BoardIterator iterator , const Piece::pinning_filter_type pinning_fn ):
	piece_(piece), iterator_(iterator), pinning_filter_(pinning_fn){}
	void operator()() noexcept;
private:
	void add_legal_moves(increment_fn_type increment_fn)   noexcept;
	void check_pinning( Piece& piece, increment_fn_type increment_fn ) noexcept;
	Piece& piece_;
	BoardIterator iterator_;
	Piece::pinning_filter_type pinning_filter_;
};

void LinearLegalMoves::add_legal_moves(const increment_fn_type increment_fn)  noexcept
{
	for (auto& square_it = this->iterator_.begin(*this->piece_.get_square());
		square_it ; increment_fn(square_it))
	{
		if (&*square_it == this->piece_.get_square()) continue;
		if (!square_it->is_free())
		{
			if (square_it->has_enemy_piece_of(this->piece_))
			{
				this->piece_.get_legal_move(square_it->get_value()) = std::make_unique<SimpleMove>();
				this->check_pinning(*square_it->get_piece(), increment_fn);
			}
			return;
		}
		this->piece_.get_legal_move(square_it->get_value()) = std::make_unique<SimpleMove>();
	}
}

void LinearLegalMoves::check_pinning(Piece& piece, const increment_fn_type increment_fn ) noexcept
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

void LinearLegalMoves::operator()() noexcept
{
	this->add_legal_moves([](BoardIterator& it) {++it; });
	this->add_legal_moves([](BoardIterator& it) {--it; });
}

using square_fn_type = bool (Square::*) (int8_t) const ;
static void base_filter(Piece& piece,  const square_fn_type predicate )
{
	auto& moves = piece.get_legal_moves();
	for (int8_t i =0 ; i < moves.size(); ++i)
	{
		if (!moves[i] || (piece.get_square()->*predicate)(i)) continue;
		piece.get_legal_move(i) = nullptr;
	}
}

void linear_moves::add_rank_squares(Piece& piece, BoardGame& board)
{
	LinearLegalMoves(piece, RankIterator(board), [](Piece& p)
	{
		base_filter(p, &Square::is_same_rank);
	})();
}

void linear_moves::add_file_squares(Piece& piece, BoardGame& board)
{
	LinearLegalMoves(piece, FileIterator(board), [](Piece& p)
	{
		base_filter(p, &Square::is_same_file);
	})();
}

void linear_moves::add_diagonal_squares(Piece& piece, BoardGame& board)
{
	LinearLegalMoves(piece, DiagonalIterator(board), [](Piece& p)
	{
		base_filter(p, &Square::is_same_diagonal);
	})();
}

void linear_moves::add_anti_diagonal_squares(Piece& piece, BoardGame& board)
{
	LinearLegalMoves(piece, AntiDiagonalIterator(board), [](Piece& p)
	{
		base_filter(p, &Square::is_same_anti_diagonal);
	})();
}

