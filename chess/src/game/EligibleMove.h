#pragma once
#include "Pin.h"
#include "Piece.h"
#include "Common.h"
#include "BoardIterator.h"

class BoardGame;

class CHESS_API EligibleMove
{
	using increment_fn_type = void (*)(BoardIterator&);
public:
	EligibleMove(BoardGame& board, Piece& piece, const BoardIterator iterator , const Piece::pinning_filter_type pinning_fn ):
	board_(board), piece_(piece), iterator_(iterator), pinning_filter_(pinning_fn){}
	EligibleMove(const EligibleMove&) = delete;
	EligibleMove(EligibleMove&&) = delete;
	EligibleMove& operator=(const EligibleMove&) = delete;
	EligibleMove& operator=(EligibleMove&&) = delete;
	virtual ~EligibleMove() = default;
	void operator()() noexcept;
protected:
	void add_eligible_squares(increment_fn_type increment_fn)   noexcept;
	void check_pinning( Piece& piece, increment_fn_type increment_fn ) noexcept;
	BoardGame& board_;
	Piece& piece_;
	BoardIterator iterator_;
	Piece::pinning_filter_type pinning_filter_;
};

class CHESS_API RankEligibleMove final: public EligibleMove
{
public:
	RankEligibleMove(BoardGame& board, Piece& piece): EligibleMove(board, piece, RankIterator(board), pin::rank_filter) {}
};

class CHESS_API FileEligibleMove final: public EligibleMove
{
public:
	FileEligibleMove(BoardGame& board, Piece& piece): EligibleMove(board, piece, FileIterator(board), pin::file_filter) {}
};


class CHESS_API DiagonalEligibleMove final: public EligibleMove
{
public:
	DiagonalEligibleMove(BoardGame& board, Piece& piece): EligibleMove(board, piece, DiagonalIterator(board), pin::diagonal_filter) {}
};


class CHESS_API AntiDiagonalEligibleMove final: public EligibleMove
{
public:
	AntiDiagonalEligibleMove(BoardGame& board, Piece& piece): EligibleMove(board, piece, AntiDiagonalIterator(board), pin::anti_diagonal_filter) {}
};
