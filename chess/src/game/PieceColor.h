#pragma once
#include <typeinfo>
#include <vector>
#include <memory>
#include "Common.h"
#include "Constants.h"
#include "Piece.h"

class WhiteColor;
class BlackColor;
class BoardGame;

class CHESS_API ColorVisitor
{
public:
	ColorVisitor() = default;
	ColorVisitor(const ColorVisitor&) = delete;
	ColorVisitor(ColorVisitor&&) = delete;
	ColorVisitor& operator=(const ColorVisitor&) = delete;
	ColorVisitor& operator=(ColorVisitor&&) = delete;
	virtual void visit(WhiteColor& color) const = 0;
	virtual void visit(BlackColor& color) const = 0;
	virtual ~ColorVisitor() = default;
};

class CHESS_API PieceColor
{
protected:
	PieceColor(BoardGame& board, const int8_t first_rank, const int8_t second_rank):
		board_(board), first_rank_(first_rank), second_rank_(second_rank) {}
public:
	PieceColor(const PieceColor&) = delete;
	PieceColor(PieceColor&&) = delete;
	PieceColor& operator=(const PieceColor&) = delete;
	PieceColor& operator=(PieceColor&&) = delete;
	virtual bool operator==(const PieceColor& other) const noexcept { return typeid(*this) == typeid(other); }
	virtual bool operator!=(const PieceColor& other) const noexcept { return !(*this == other); }
	virtual ~PieceColor() = default;
	virtual void accept(const ColorVisitor& visitor) = 0;
	void init_valuable_pieces() noexcept;
	void init_pawns() noexcept;
	int8_t get_first_rank() const noexcept { return this->first_rank_; }
	int8_t get_second_rank() const noexcept { return this->second_rank_; }
protected:
	using pieces_type = std::vector<std::unique_ptr<Piece>>;
	pieces_type pieces_;
	BoardGame& board_;
	int8_t first_rank_;
	int8_t second_rank_;
};

class CHESS_API BlackColor final: public PieceColor
{
public:
	BlackColor(BoardGame& board) : PieceColor(board, 0, 1) {}
	void accept(const ColorVisitor& visitor) override { visitor.visit(*this); }
};

class CHESS_API WhiteColor final: public PieceColor
{
public:
	WhiteColor(BoardGame& board) : PieceColor(board, NB_ROWS - 1, NB_ROWS - 2) {}
	void accept(const ColorVisitor& visitor) override { visitor.visit(*this); }
};
