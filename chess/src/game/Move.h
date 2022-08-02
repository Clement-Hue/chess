#pragma once
#include "../Common.h"

class Piece;
class Rock;
class Square;
class Pawn;
class PieceColor;

class CHESS_API Move
{
public:
	Move() = default;
	Move(Move&&) = default;
	Move(const Move&) = default;
	Move& operator=(Move&&) = default;
	Move& operator=(const Move&) = delete;
	virtual ~Move() = default;
	virtual bool operator()(Piece&, Square&) = 0;
};

class CHESS_API SimpleMove final: public Move
{
public:
	bool operator()(Piece&, Square&) override;
};

class CHESS_API CastleMove final: public Move
{
public:
	CastleMove(Piece& rock,Square& king_square, Square& rock_square): king_square_(king_square), rock_square_(rock_square), rock_(rock)  {}
	bool operator()(Piece&, Square&) override;
private:
	Square& king_square_;
	Square& rock_square_;
	Piece& rock_;
};

class CHESS_API PromoteMove final: public Move
{
public:
	PromoteMove(PieceColor& color) : color_(color) {}
	bool operator()(Piece&, Square&) override;
private:
	PieceColor& color_;

};

class CHESS_API PawnDoubleMove final: public Move
{
	bool operator()(Piece&, Square&) override;
};

class CHESS_API InPassingMove final: public Move
{
public:
	InPassingMove(Pawn& taken_pawn): taken_pawn_(taken_pawn) {}
	bool operator()(Piece&, Square&) override;
private:
	Pawn& taken_pawn_;
};
