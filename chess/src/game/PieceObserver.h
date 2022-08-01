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
	virtual void on_add(const Pawn&) noexcept = 0;
	virtual void on_add(const King&) noexcept = 0;
	virtual void on_add(const Queen&) noexcept = 0;
	virtual void on_add(const Rock&) noexcept = 0;
	virtual void on_add(const Bishop&) noexcept = 0;
	virtual void on_add(const Knight&) noexcept = 0;
	virtual ~PieceObserver() = default;
};

