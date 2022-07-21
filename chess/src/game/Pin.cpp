#include "Pin.h"

using square_fn_type = bool (Square::*) (const Square&) const ;
static void base_filter(Piece& piece,  const square_fn_type predicate )
{
	auto& eligible_squares = piece.get_eligible_squares();
	for (int8_t i =0 ; i < eligible_squares.size(); ++i)
	{
		if (!eligible_squares[i] || (piece.get_square()->*predicate)(*eligible_squares[i])) continue;
		piece.get_eligible_square(i) = nullptr;
	}
}

void pin::rank_filter(Piece& piece)
{
	base_filter(piece, &Square::is_same_rank);
}

void pin::file_filter(Piece& piece)
{
	base_filter(piece, &Square::is_same_file);
}

void pin::diagonal_filter(Piece& piece)
{
	base_filter(piece, &Square::is_same_diagonal);
}

void pin::anti_diagonal_filter(Piece& piece)
{
	base_filter(piece, &Square::is_same_anti_diagonal);
}
