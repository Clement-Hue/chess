#pragma once
#include "Pin.h"
#include "Piece.h"
#include "Common.h"
#include "BoardIterator.h"

class BoardGame;

class CHESS_API LinearEligibleMove
{
	using increment_fn_type = void (*)(BoardIterator&);
public:
	LinearEligibleMove(Piece& piece, const BoardIterator iterator , const Piece::pinning_filter_type pinning_fn ):
	piece_(piece), iterator_(iterator), pinning_filter_(pinning_fn){}
	LinearEligibleMove(const LinearEligibleMove&) = delete;
	LinearEligibleMove(LinearEligibleMove&&) = delete;
	LinearEligibleMove& operator=(const LinearEligibleMove&) = delete;
	LinearEligibleMove& operator=(LinearEligibleMove&&) = delete;
	~LinearEligibleMove() = default;
	void operator()() noexcept;
protected:
	void add_eligible_squares(increment_fn_type increment_fn)   noexcept;
	void check_pinning( Piece& piece, increment_fn_type increment_fn ) noexcept;
	Piece& piece_;
	BoardIterator iterator_;
	Piece::pinning_filter_type pinning_filter_;
};

class CHESS_API RankEligibleMove final: public LinearEligibleMove
{
public:
	RankEligibleMove(BoardGame& board, Piece& piece): LinearEligibleMove( piece, RankIterator(board), pin::rank_filter) {}
};

class CHESS_API FileEligibleMove final: public LinearEligibleMove
{
public:
	FileEligibleMove(BoardGame& board, Piece& piece): LinearEligibleMove( piece, FileIterator(board), pin::file_filter) {}
};


class CHESS_API DiagonalEligibleMove final: public LinearEligibleMove
{
public:
	DiagonalEligibleMove(BoardGame& board, Piece& piece): LinearEligibleMove( piece, DiagonalIterator(board), pin::diagonal_filter) {}
};


class CHESS_API AntiDiagonalEligibleMove final: public LinearEligibleMove
{
public:
	AntiDiagonalEligibleMove(BoardGame& board, Piece& piece): LinearEligibleMove( piece, AntiDiagonalIterator(board), pin::anti_diagonal_filter) {}
};
