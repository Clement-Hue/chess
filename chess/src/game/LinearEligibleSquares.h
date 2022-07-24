#pragma once
#include "Pin.h"
#include "Piece.h"
#include "Common.h"

class BoardGame;

namespace linear_eligible_squares
{
	CHESS_API void add_rank_squares(Piece& piece, BoardGame& board);
	CHESS_API void add_file_squares(Piece& piece, BoardGame& board);
	CHESS_API void add_diagonal_squares(Piece& piece, BoardGame& board);
	CHESS_API void add_anti_diagonal_squares(Piece& piece, BoardGame& board);
}

