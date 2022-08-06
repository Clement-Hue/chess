#pragma once
#include "../Common.h"
#include "Constants.h"
#include "Square.h"
#include <cstdint>


class BoardGame;

class CHESS_API BoardIterator
{
	using square_fn_type = bool (Square::*) (int8_t) const ;
public:
	BoardIterator(BoardGame& board, const int8_t offset, const square_fn_type predicate)
	: board_(board), offset_(offset), predicate_(predicate) {}
	BoardIterator& begin(const Square& square) noexcept;
	BoardIterator& operator+=(const int8_t i) noexcept
	{
		this->square_value_ += i * this->offset_;
		return *this;
	}
	BoardIterator& operator-=(const int8_t i) noexcept
	{
		this->square_value_ -= i * this->offset_;
		return *this;
	}
	BoardIterator& operator++() noexcept
	{
		this->square_value_ += this->offset_;
		return *this;
	};
	BoardIterator operator++(int) noexcept
	{
		BoardIterator iterator =  *this ;
		++*this;
		return iterator;
	};
	BoardIterator& operator--() noexcept
	{
		this->square_value_ -= this->offset_;
		return *this;
	};
	BoardIterator operator--(int) noexcept
	{
		BoardIterator iterator =  *this ;
		--*this;
		return iterator;
	};
	explicit operator bool() const noexcept;
	Square& operator*() const noexcept;
	bool operator==(const BoardIterator& other) const noexcept
	{
		if (!other.square_ || !this->square_) return false;
		return other->get_value() == (*this)->get_value();
	}
	bool operator!=(const BoardIterator& other) const noexcept
	{
		return !(*this == other);
	}
	Square* operator->() const noexcept
	{
		return &**this;
	}
protected:
	const Square* square_{nullptr};
	int8_t square_value_{0};
private:
	BoardGame& board_;
	int8_t offset_;
	square_fn_type predicate_;
};

class CHESS_API RankIterator final: public BoardIterator
{
public:
	explicit RankIterator(BoardGame& board): BoardIterator(board, 1, &Square::is_same_rank) {}
};


class CHESS_API FileIterator final: public BoardIterator
{
public:
	explicit FileIterator(BoardGame& board): BoardIterator(board, NB_COLUMNS, &Square::is_same_file) {}
};


class CHESS_API DiagonalIterator final: public BoardIterator
{
public:
	explicit DiagonalIterator(BoardGame& board): BoardIterator(board, NB_COLUMNS - 1, &Square::is_same_diagonal) {}
};


class CHESS_API AntiDiagonalIterator final: public BoardIterator
{
public:
	explicit AntiDiagonalIterator(BoardGame& board): BoardIterator(board, NB_COLUMNS + 1, &Square::is_same_anti_diagonal) {}
};
