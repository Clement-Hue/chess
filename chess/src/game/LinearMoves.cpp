#include "LinearMoves.h"
#include "BoardGame.h"
#include "Move.h"

using increment_fn_type = void (*)(BoardIterator&);
template <typename Iterator>
class AddLinearLegalMoves
{
public:
	AddLinearLegalMoves(Piece& piece, BoardGame& board  ):
	piece_(piece), board_(board) {}
	void operator()() noexcept;
private:
	void add_legal_moves(increment_fn_type increment_fn)   noexcept;
	Piece& piece_;
	BoardGame& board_;
};

template <typename Iterator>
void AddLinearLegalMoves<Iterator>::add_legal_moves(const increment_fn_type increment_fn)  noexcept
{
	for (auto& square_it = Iterator(this->board_).begin(*this->piece_.get_square());
		square_it ; increment_fn(square_it))
	{
		if (&*square_it == this->piece_.get_square()) continue;
		if (!square_it->has_friend_piece_of(this->piece_))
		{
			this->piece_.get_legal_move(square_it->get_value()) = std::make_unique<SimpleMove>();
		}
		if (!square_it->is_free())
		{
			return;
		}
	}
}

template <typename Iterator>
void AddLinearLegalMoves<Iterator>::operator()() noexcept
{
	this->add_legal_moves([](BoardIterator& it) {++it; });
	this->add_legal_moves([](BoardIterator& it) {--it; });
}

template <typename Iterator>
class RemoveIllegalMoves
{
	using pinning_filter_type = void(*)(Piece&);
public:
	RemoveIllegalMoves(Piece& piece,PieceColor& enemy_color,BoardGame& board, const pinning_filter_type pinning_filter ):
	piece_(piece), pinning_filter_(pinning_filter), enemy_color_(enemy_color), board_(board){}
	void operator()() noexcept;
private:
	void remove_illegal_moves(increment_fn_type increment_fn)  noexcept;
	void check_pinning(Piece&, increment_fn_type) const noexcept;
	void clear_legal_moves_except(const Square& start, const Square& end, increment_fn_type increment_fn) const noexcept;
	Piece& piece_;
	pinning_filter_type pinning_filter_;
	PieceColor& enemy_color_;
	BoardGame& board_;
};

template <typename Iterator>
void RemoveIllegalMoves<Iterator>::remove_illegal_moves(const increment_fn_type increment_fn) noexcept
{
	const auto& enemy_king = this->enemy_color_.get_king();
	if (!enemy_king) return;
	for (auto& square_it = Iterator(this->board_).begin(*this->piece_.get_square());
		square_it ; increment_fn(square_it))
	{
		if (&*square_it == this->piece_.get_square()) continue;
		enemy_king->clear_move(*square_it);
		if (square_it->get_piece() == enemy_king) // check
		{
			this->clear_legal_moves_except(*this->piece_.get_square(), *square_it, increment_fn);
		}
		if (square_it->has_enemy_piece_of(this->piece_))
		{
			this->check_pinning(*square_it->get_piece(), increment_fn);
		}
		if (!square_it->is_free() && square_it->get_piece() != enemy_king)
		{
			return;
		}
	}
}


template <typename Iterator>
void RemoveIllegalMoves<Iterator>::check_pinning(Piece& piece, const increment_fn_type increment_fn ) const noexcept
{
	const auto& king = this->enemy_color_.get_king();
	for (auto& square_it= Iterator(this->board_).begin(*piece.get_square());
		square_it && !square_it->has_friend_piece_of(this->piece_)
		; increment_fn(square_it))
	{
		if (&*square_it == piece.get_square()) continue;
		if (square_it->has_enemy_piece_of(this->piece_))
		{
			if (square_it->get_piece() == king)
			{
				this->pinning_filter_(piece);
			}
			return;
		}
	}
}

/**
 * Clear all legal moves except the squares between the start include and the end exclude
 */
template <typename Iterator>
void RemoveIllegalMoves<Iterator>::clear_legal_moves_except(const Square& start, const Square& end, const increment_fn_type increment_fn) const noexcept
{
	std::vector<int8_t> legal_moves;
	for (auto& square_it = Iterator(this->board_).begin(start); square_it && *square_it != end; increment_fn(square_it))
	{
		legal_moves.emplace_back(square_it->get_value());
	}
	this->enemy_color_.clear_legal_moves_except(legal_moves);
}

template <typename Iterator>
void RemoveIllegalMoves<Iterator>::operator()() noexcept
{
	this->remove_illegal_moves([](BoardIterator& it) {++it; });
	this->remove_illegal_moves([](BoardIterator& it) {--it; });
}


using square_fn_type = bool (Square::*) (int8_t) const ;
static void base_filter(Piece& piece,  const square_fn_type predicate )
{
	const auto& moves = piece.get_legal_moves();
	for (int8_t i =0 ; i < moves.size(); ++i)
	{
		if (!moves[i] || (piece.get_square()->*predicate)(i)) continue;
		piece.get_legal_move(i) = nullptr;
	}
}

void linear_moves::add_rank_moves(Piece& piece, BoardGame& board)
{
	AddLinearLegalMoves<RankIterator>(piece, board)();
}

void linear_moves::add_file_moves(Piece& piece, BoardGame& board)
{
	AddLinearLegalMoves<FileIterator>(piece, board)();
}

void linear_moves::add_diagonal_moves(Piece& piece, BoardGame& board)
{
	AddLinearLegalMoves<DiagonalIterator>(piece, board)();
}

void linear_moves::add_anti_diagonal_moves(Piece& piece, BoardGame& board)
{
	AddLinearLegalMoves<AntiDiagonalIterator>(piece, board)();
}

void linear_moves::remove_illegal_rank_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color)
{
	RemoveIllegalMoves<RankIterator>(piece, enemy_color,board, [](Piece& piece)
	{
			base_filter(piece, &Square::is_same_rank);
	})();
}

void linear_moves::remove_illegal_file_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color)
{
	RemoveIllegalMoves<FileIterator>(piece,enemy_color ,board, [](Piece& p)
		{
			base_filter(p, &Square::is_same_file);
		})();
}

void linear_moves::remove_illegal_diagonal_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color)
{
	RemoveIllegalMoves<DiagonalIterator>(piece,enemy_color ,board, [](Piece& p)
		{
			base_filter(p, &Square::is_same_diagonal);
		})();
}

void linear_moves::remove_illegal_anti_diagonal_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color)
{
	RemoveIllegalMoves<AntiDiagonalIterator>(piece,enemy_color ,board, [](Piece& p)
		{
			base_filter(p, &Square::is_same_anti_diagonal);
		})();
}


