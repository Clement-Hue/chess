#pragma once
#include <typeinfo>
#include "Common.h"
#include "Constants.h"

class WhiteColor;
class BlackColor;

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
	PieceColor() = default;
public:
	PieceColor(const PieceColor&) = default;
	PieceColor(PieceColor&&) = default;
	PieceColor& operator=(const PieceColor&) = delete;
	PieceColor& operator=(PieceColor&&) = delete;
	virtual bool operator==(const PieceColor& other) const noexcept { return typeid(*this) == typeid(other); }
	virtual bool operator!=(const PieceColor& other) const noexcept { return !(*this == other); }
	virtual ~PieceColor() = default;
	virtual void accept(const ColorVisitor& visitor) = 0;
};

class CHESS_API BlackColor final: public PieceColor
{
public:
	static constexpr  int8_t first_rank = 0;
	static constexpr  int8_t second_rank = first_rank + 1;
	BlackColor() : PieceColor() {}
	void accept(const ColorVisitor& visitor) override { visitor.visit(*this); }
};

class CHESS_API WhiteColor final: public PieceColor
{
public:
	static constexpr  int8_t first_rank = NB_ROWS - 1;
	static constexpr  int8_t second_rank = first_rank - 1;
	WhiteColor() : PieceColor() {}
	void accept(const ColorVisitor& visitor) override { visitor.visit(*this); }
};
