#include "Move.h"
#include "Square.h"
#include "Piece.h"

static void move_piece_to_square(Piece& piece, Square& square) noexcept
{
	piece.get_square()->remove_piece();
	piece.set_square(square);
	square.set_piece(piece);
}

bool SimpleMove::operator()(Piece& piece, Square& square)
{
	if ( Piece* const piece_on_square = square.get_piece();
		piece_on_square && piece_on_square->is_enemy_of(piece))
	{
		piece_on_square->remove_square();
	}
	move_piece_to_square(piece, square);
	piece.mark_as_moved();
	return true;
}

bool CastleMove::operator()(Piece& king, Square&)
{
	move_piece_to_square(king, king_square_);
	move_piece_to_square(this->rock_, rock_square_);
	king.mark_as_moved();
	this->rock_.mark_as_moved();
	return true;
}

