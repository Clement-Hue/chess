#pragma once
#include "Piece.h"
#include "Common.h"
#include "Pin.h"

class BoardGame;

class CHESS_API EligibleMove
{
public:
	EligibleMove(BoardGame& board, Piece& piece, const int8_t offset, const Piece::pinning_filter_type pinning_fn ):
	board_(board), piece_(piece), offset_(offset), pinning_filter_(pinning_fn){}
	EligibleMove(const EligibleMove&) = delete;
	EligibleMove(EligibleMove&&) = delete;
	EligibleMove& operator=(const EligibleMove&) = delete;
	EligibleMove& operator=(EligibleMove&&) = delete;
	virtual ~EligibleMove() = default;
	void operator()() const noexcept;
protected:
	void add_eligible_squares(int8_t offset )  const noexcept;
	virtual bool is_eligible_square(const Square&) const noexcept = 0;
	void check_pinning( Piece& piece, int8_t offset )const  noexcept;
	BoardGame& board_;
	Piece& piece_;
	int8_t offset_;
	Piece::pinning_filter_type pinning_filter_;
};

class CHESS_API RankEligibleMove final: public EligibleMove
{
public:
	RankEligibleMove(BoardGame& board, Piece& piece): EligibleMove(board, piece, 1, pin::rank_filter){}
private:
	bool is_eligible_square(const Square& square) const noexcept override { return this->piece_.get_square()->is_same_rank(square); }
};

class CHESS_API FileEligibleMove final: public EligibleMove
{
public:
	FileEligibleMove(BoardGame& board, Piece& piece): EligibleMove(board, piece, NB_SQUARES_BY_ROW, pin::file_filter){}
private:
	bool is_eligible_square(const Square& square) const noexcept override { return this->piece_.get_square()->is_same_file(square); }
};


class CHESS_API DiagonalEligibleMove final: public EligibleMove
{
public:
	DiagonalEligibleMove(BoardGame& board, Piece& piece): EligibleMove(board, piece, NB_SQUARES_BY_ROW - 1, pin::diagonal_filter){}
private:
	bool is_eligible_square(const Square& square) const noexcept override { return this->piece_.get_square()->is_same_diagonal(square); }
};


class CHESS_API AntiDiagonalEligibleMove final: public EligibleMove
{
public:
	AntiDiagonalEligibleMove(BoardGame& board, Piece& piece): EligibleMove(board, piece, NB_SQUARES_BY_ROW + 1, pin::anti_diagonal_filter){}
private:
	bool is_eligible_square(const Square& square) const noexcept override { return this->piece_.get_square()->is_same_anti_diagonal(square); }
};
