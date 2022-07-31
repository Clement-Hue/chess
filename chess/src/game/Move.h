#pragma once

class Piece;
class Square;
class Pawn;

class Move
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

class SimpleMove final: public Move
{
public:
	bool operator()(Piece&, Square&) override;
};

class CastleMove final: public Move
{
public:
	CastleMove(Square& king_square, Square& rock_square): king_square_(king_square), rock_square_(rock_square)  {}
	bool operator()(Piece&, Square&) override { return true; }
private:
	Square& king_square_;
	Square& rock_square_;
};

class PromoteMove final: public Move
{
public:
	bool operator()(Piece&, Square&) override { return true; }
};

class InPassingMove final: public Move
{
public:
	InPassingMove(Pawn& taken_pawn): taken_pawn_(taken_pawn) {}
	bool operator()(Piece&, Square&) override { return true; }
private:
	Pawn& taken_pawn_;
};