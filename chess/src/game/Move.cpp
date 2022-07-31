#include "Move.h"
#include "Square.h"
#include "Piece.h"

bool SimpleMove::operator()(Piece& piece, Square& square)
{
	Piece* const piece_on_square = square.get_piece();
	if (piece_on_square && piece_on_square->is_friend_of(piece)) return false;
	if (piece_on_square && piece_on_square->is_enemy_of(piece))
	{
		piece_on_square->remove_square();
	}
	piece.get_square()->remove_piece();
	piece.set_square(square);
	square.set_piece(piece);
	piece.mark_as_moved();
	return true;
}
