#pragma once
#include <typeinfo>
#include <vector>
#include <memory>

#include "../Common.h"
#include "Constants.h"
#include "Piece.h"

class WhiteColor;
class BlackColor;
class BoardGame;

struct Rank
{
	int8_t first, second;
};

class ColorVisitor
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
	using pieces_type = std::vector<std::unique_ptr<Piece>>;
	PieceColor(BoardGame& board, const Rank rank): board_(board), rank_(rank) {}
public:
	PieceColor(const PieceColor&) = delete;
	PieceColor(PieceColor&&) = delete;
	PieceColor& operator=(const PieceColor&) = delete;
	PieceColor& operator=(PieceColor&&) = delete;
	virtual bool operator==(const PieceColor& other) const noexcept { return typeid(*this) == typeid(other); }
	virtual bool operator!=(const PieceColor& other) const noexcept { return !(*this == other); }
	virtual ~PieceColor() = default;
	virtual void accept(const ColorVisitor& visitor) = 0;
	BoardGame& get_board() const noexcept { return this->board_; }
	const pieces_type& get_pieces() noexcept { return this->pieces_; }
	void clear_legal_moves_states() const noexcept;
	Piece& get_piece(const int8_t i) const noexcept { return *this->pieces_[i]; }
	template <typename P>
	P& add_piece(Square& square) noexcept;
	bool is_turn() const noexcept;
	Rank get_rank() const noexcept { return this->rank_; }
	void compute_legal_moves() const noexcept;
	void compute_pseudo_legal_moves() const noexcept;
	void set_default_pieces() noexcept;
	bool is_square_attacked(const Square&) const noexcept;
protected:
	pieces_type pieces_;
	BoardGame& board_;
	Rank rank_;
};

class CHESS_API BlackColor final: public PieceColor
{
public:
	BlackColor(BoardGame& board) : PieceColor(board, {0,1}) {}
	void accept(const ColorVisitor& visitor) override { visitor.visit(*this); }
};

class CHESS_API WhiteColor final: public PieceColor
{
public:
	WhiteColor(BoardGame& board) : PieceColor(board, {NB_ROWS-1, NB_ROWS -2}) {}
	void accept(const ColorVisitor& visitor) override { visitor.visit(*this); }
};

template <typename P>
P& PieceColor::add_piece(Square& square) noexcept
{
	auto piece_pt = std::make_unique<P>(&square, *this);
	P& piece  = *piece_pt;
	this->pieces_.emplace_back(std::move(piece_pt));
	return piece;
}






