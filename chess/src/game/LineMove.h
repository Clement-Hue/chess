#pragma once
#include "Piece.h"
#include "Common.h"

class BoardGame;

class CHESS_API LineMove
{
public:
	using e_squares_type = std::array<Square*, NB_SQUARES>;
	LineMove(BoardGame& board, const Piece& piece ): board_(board), piece_(piece) {}
	LineMove(const LineMove&) = delete;
	LineMove(LineMove&&) = delete;
	LineMove& operator=(LineMove&&) = delete;
	LineMove& operator=(const LineMove&) = delete;
	void add_eligible_squares(e_squares_type& squares) const noexcept;
	virtual ~LineMove() = default;
	void check_pinning(const Piece& square) const noexcept;
protected:
	virtual bool is_eligible_square(Square& square) const noexcept = 0;
	virtual int8_t get_offset() const noexcept = 0;
	BoardGame& board_;
	const Piece& piece_;
};

class ForthFileMove final: public LineMove
{
public:
	ForthFileMove(BoardGame& board, const Piece& piece): LineMove(board, piece) {}
private:
	int8_t get_offset() const noexcept override { return NB_SQUARES_BY_ROW; }
	bool is_eligible_square(Square& square) const noexcept override { return square.is_same_file(*this->piece_.get_square()); }
};


class BackFileMove final: public LineMove
{
public:
	BackFileMove(BoardGame& board, const Piece& piece): LineMove(board, piece) {}
private:
	int8_t get_offset() const noexcept override { return -NB_SQUARES_BY_ROW; }
	bool is_eligible_square(Square& square) const noexcept override { return square.is_same_file(*this->piece_.get_square()); }
};

class ForthRankMove final: public LineMove
{
public:
	ForthRankMove(BoardGame& board, const Piece& piece): LineMove(board, piece) {}
private:
	int8_t get_offset() const noexcept override { return 1; }
	bool is_eligible_square(Square& square) const noexcept override { return square.is_same_rank(*this->piece_.get_square()); }
};


class BackRankMove final: public LineMove
{
public:
	BackRankMove(BoardGame& board, const Piece& piece): LineMove(board, piece) {}
private:
	int8_t get_offset() const noexcept override { return -1; }
	bool is_eligible_square(Square& square) const noexcept override { return square.is_same_rank(*this->piece_.get_square()); }
};

class ForthDiagonalMove final: public LineMove
{
public:
	ForthDiagonalMove(BoardGame& board, const Piece& piece): LineMove(board, piece) {}
private:
	int8_t get_offset() const noexcept override { return 7; }
	bool is_eligible_square(Square& square) const noexcept override { return square.is_same_diagonal(*this->piece_.get_square()); }
};

class BackDiagonalMove final: public LineMove
{
public:
	BackDiagonalMove(BoardGame& board, const Piece& piece): LineMove(board, piece) {}
private:
	int8_t get_offset() const noexcept override { return -7; }
	bool is_eligible_square(Square& square) const noexcept override { return square.is_same_diagonal(*this->piece_.get_square()); }
};



class ForthAntiDiagonalMove final: public LineMove
{
public:
	ForthAntiDiagonalMove(BoardGame& board, const Piece& piece): LineMove(board, piece) {}
private:
	int8_t get_offset() const noexcept override { return 9; }
	bool is_eligible_square(Square& square) const noexcept override { return square.is_same_diagonal(*this->piece_.get_square()); }
};

class BackAntiDiagonalMove final: public LineMove
{
public:
	BackAntiDiagonalMove(BoardGame& board, const Piece& piece): LineMove(board, piece) {}
private:
	int8_t get_offset() const noexcept override { return -9; }
	bool is_eligible_square(Square& square) const noexcept override { return square.is_same_diagonal(*this->piece_.get_square()); }
};

