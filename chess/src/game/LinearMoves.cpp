#include "LinearMoves.h"
#include "BoardGame.h"
#include "Move.h"

using increment_fn_type = void (*)(BoardIterator&);
class AddLinearLegalMoves
{
public:
	AddLinearLegalMoves(Piece& piece, const BoardIterator iterator  ):
	piece_(piece), iterator_(iterator) {}
	void operator()() noexcept;
private:
	void add_legal_moves(increment_fn_type increment_fn)   noexcept;
	Piece& piece_;
	BoardIterator iterator_;
};

void AddLinearLegalMoves::add_legal_moves(const increment_fn_type increment_fn)  noexcept
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
			}
			return;
		}
		this->piece_.get_legal_move(square_it->get_value()) = std::make_unique<SimpleMove>();
	}
}

void AddLinearLegalMoves::operator()() noexcept
{
	this->add_legal_moves([](BoardIterator& it) {++it; });
	this->add_legal_moves([](BoardIterator& it) {--it; });
}

class RemoveIllegalMoves
{
	using pinning_filter_type = void(*)(Piece&);
public:
	RemoveIllegalMoves(Piece& piece,PieceColor& enemy_color, const BoardIterator iterator, const pinning_filter_type pinning_filter ):
	piece_(piece), iterator_(iterator), pinning_filter_(pinning_filter), enemy_color_(enemy_color) {}
	void operator()() noexcept;
private:
	void remove_illegal_moves(increment_fn_type increment_fn)  noexcept;
	void check_pinning(Piece&, increment_fn_type) noexcept;
	Piece& piece_;
	BoardIterator iterator_;
	pinning_filter_type pinning_filter_;
	PieceColor& enemy_color_;
};

void RemoveIllegalMoves::remove_illegal_moves(const increment_fn_type increment_fn) noexcept
{
	const auto& king = this->enemy_color_.get_king();
	for (auto& square_it = this->iterator_.begin(*this->piece_.get_square());
		square_it ; increment_fn(square_it))
	{
		if (&*square_it == this->piece_.get_square()) continue;
		if (square_it->has_enemy_piece_of(this->piece_) && dynamic_cast<King*>(square_it->get_piece()))
		{
			continue;
		}
		if (king && !square_it->has_friend_piece_of(*king)) // otherwise the rock is not selectable to castle
		{
			king->get_legal_move(square_it->get_value()) = nullptr;
		}
		if (square_it->has_enemy_piece_of(this->piece_))
		{
			this->check_pinning(*square_it->get_piece(), increment_fn);
		}
		if (!square_it->is_free())
		{
			return;
		}
	}
}


void RemoveIllegalMoves::check_pinning(Piece& piece, const increment_fn_type increment_fn ) noexcept
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
				this->pinning_filter_(piece);
			}
			return;
		}
	}
}

void RemoveIllegalMoves::operator()() noexcept
{
	this->remove_illegal_moves([](BoardIterator& it) {++it; });
	this->remove_illegal_moves([](BoardIterator& it) {--it; });
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

void linear_moves::add_rank_moves(Piece& piece, BoardGame& board)
{
	AddLinearLegalMoves(piece, RankIterator(board))();
}

void linear_moves::add_file_moves(Piece& piece, BoardGame& board)
{
	AddLinearLegalMoves(piece, FileIterator(board))();
}

void linear_moves::add_diagonal_moves(Piece& piece, BoardGame& board)
{
	AddLinearLegalMoves(piece, DiagonalIterator(board))();
}

void linear_moves::add_anti_diagonal_moves(Piece& piece, BoardGame& board)
{
	AddLinearLegalMoves(piece, AntiDiagonalIterator(board))();
}

void linear_moves::remove_illegal_rank_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color)
{
	RemoveIllegalMoves(piece, enemy_color,RankIterator(board), [](Piece& piece)
	{
			base_filter(piece, &Square::is_same_rank);
	})();
}

void linear_moves::remove_illegal_file_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color)
{
	RemoveIllegalMoves(piece,enemy_color ,FileIterator(board), [](Piece& p)
		{
			base_filter(p, &Square::is_same_file);
		})();
}

void linear_moves::remove_illegal_diagonal_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color)
{
	RemoveIllegalMoves(piece,enemy_color ,DiagonalIterator(board), [](Piece& p)
		{
			base_filter(p, &Square::is_same_diagonal);
		})();
}

void linear_moves::remove_illegal_anti_diagonal_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color)
{
	RemoveIllegalMoves(piece,enemy_color ,AntiDiagonalIterator(board), [](Piece& p)
		{
			base_filter(p, &Square::is_same_anti_diagonal);
		})();
}


