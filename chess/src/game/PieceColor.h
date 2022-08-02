#pragma once
#include <typeinfo>
#include <vector>
#include <memory>

#include "../Common.h"
#include "PieceObserver.h"
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
	ColorVisitor(const ColorVisitor&) = default;
	ColorVisitor(ColorVisitor&&) = default;
	ColorVisitor& operator=(const ColorVisitor&) = delete;
	ColorVisitor& operator=(ColorVisitor&&) = delete;
	virtual void visit(WhiteColor& color) const = 0;
	virtual void visit(BlackColor& color) const = 0;
	virtual ~ColorVisitor() = default;
};

class CHESS_API PieceColor
{
protected:
	using piece_obs_type = std::vector<std::unique_ptr<PieceObserver>>;
	using pieces_type = std::vector<std::unique_ptr<Piece>>;
	PieceColor(BoardGame& board, const Rank rank, piece_obs_type piece_observers): board_(board),
	rank_(rank), piece_observers_(std::move(piece_observers)) {}
public:
	PieceColor(const PieceColor&) = delete;
	PieceColor(PieceColor&&) = delete;
	PieceColor& operator=(const PieceColor&) = delete;
	PieceColor& operator=(PieceColor&&) = delete;
	virtual bool operator==(const PieceColor& other) const noexcept { return typeid(*this) == typeid(other); }
	virtual bool operator!=(const PieceColor& other) const noexcept { return !(*this == other); }
	virtual ~PieceColor() = default;
	virtual void accept(const ColorVisitor& visitor) = 0;
	void add_piece_observer(std::unique_ptr<PieceObserver>) noexcept;
	BoardGame& get_board() const noexcept { return this->board_; }
	pieces_type& get_pieces() noexcept { return this->pieces_; }
	void clear_legal_moves_states() const noexcept;
	Piece& get_piece(const int8_t i) const noexcept { return *this->pieces_[i]; }
	bool is_turn() const noexcept;
	Rank get_rank() const noexcept { return this->rank_; }
	void compute_legal_moves() const noexcept;
	void compute_pseudo_legal_moves() const noexcept;
	void set_default_pieces() noexcept;
	bool is_square_attacked(const Square&) const noexcept;
	template <typename P>
	P& add_piece(Square& square) noexcept;
	template <typename P>
	void add_piece_notify(P&)  const noexcept;
	void remove_piece(Piece& piece) noexcept;
protected:
	pieces_type pieces_;
	BoardGame& board_;
	Rank rank_;
	piece_obs_type piece_observers_;
};

class CHESS_API BlackColor final: public PieceColor
{
public:
	BlackColor(BoardGame& board, piece_obs_type piece_observers = {}) : PieceColor(board, {0,1}, std::move(piece_observers)) {}
	void accept(const ColorVisitor& visitor) override { visitor.visit(*this); }
};

class CHESS_API WhiteColor final: public PieceColor
{
public:
	WhiteColor(BoardGame& board, piece_obs_type piece_observers = {}) : PieceColor(board, {NB_ROWS-1, NB_ROWS -2}, std::move(piece_observers)) {}
	void accept(const ColorVisitor& visitor) override { visitor.visit(*this); }
};

template <typename P>
void PieceColor::add_piece_notify(P& piece) const noexcept
{
	for (auto& obs: this->piece_observers_)
	{
		obs->on_add(piece);
	}
}


template <typename P>
P& PieceColor::add_piece(Square& square) noexcept
{
	auto piece_pt = std::make_unique<P>(&square, *this);
	P& piece  = *piece_pt;
	this->pieces_.emplace_back(std::move(piece_pt));
	this->add_piece_notify(piece);
	return piece;
}






