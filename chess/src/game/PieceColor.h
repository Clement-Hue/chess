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
public:
	using pieces_type = std::vector<std::unique_ptr<Piece>>;
	explicit PieceColor(BoardGame* board = nullptr ): board_(board) {}
	PieceColor(const PieceColor&) = delete;
	PieceColor(PieceColor&&) = delete;
	PieceColor& operator=(const PieceColor&) = delete;
	PieceColor& operator=(PieceColor&&) = delete;
	virtual bool operator==(const PieceColor& other) const noexcept { return typeid(*this) == typeid(other); }
	virtual bool operator!=(const PieceColor& other) const noexcept { return !(*this == other); }
	virtual ~PieceColor() = default;
	virtual void accept(const ColorVisitor& visitor) = 0;
	BoardGame& get_board() const noexcept { return *this->board_; }
	const pieces_type& get_pieces() noexcept { return this->pieces_; }
	Piece& get_piece(const int8_t i) const noexcept { return *this->pieces_[i]; }
	bool is_turn() const noexcept;
	void compute_legal_squares() const noexcept;
	void compute_pseudo_legal_squares() const noexcept;
	void set_board(BoardGame& board) noexcept { this->board_ = &board; }
	void set_pieces(pieces_type pieces) noexcept;
	void add_piece(std::unique_ptr<Piece> piece) noexcept;
	void clear_pieces() noexcept { this->pieces_.clear()  ; }
	virtual void set_default_pieces() noexcept = 0;
protected:
	pieces_type pieces_;
	BoardGame* board_{nullptr};
};

class CHESS_API BlackColor final: public PieceColor
{
public:
	explicit BlackColor(BoardGame* board): PieceColor(board) {}
	void set_default_pieces() noexcept override;
	void accept(const ColorVisitor& visitor) override { visitor.visit(*this); }
};

class CHESS_API WhiteColor final: public PieceColor
{
public:
	explicit WhiteColor(BoardGame* board ): PieceColor(board) {}
	void set_default_pieces() noexcept override;
	void accept(const ColorVisitor& visitor) override { visitor.visit(*this); }
};


