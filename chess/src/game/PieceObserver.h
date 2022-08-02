#pragma once
#include "../Common.h"
class Pawn;
class King;
class Queen;
class Bishop;
class Rock;
class Knight;

class CHESS_API PieceObserver
{
public:
	PieceObserver() = default;
	PieceObserver(const PieceObserver&) = default;
	PieceObserver(PieceObserver&&) = default;
	PieceObserver& operator=(PieceObserver&&) = default;
	PieceObserver& operator=(const PieceObserver&) = default;
	virtual void on_add(Pawn&) const noexcept = 0;
	virtual void on_add(King&) const noexcept = 0;
	virtual void on_add(Queen&) const noexcept = 0;
	virtual void on_add(Rock&) const noexcept = 0;
	virtual void on_add(Bishop&) const noexcept = 0;
	virtual void on_add(Knight&) const noexcept = 0;
	virtual ~PieceObserver() = default;
};

