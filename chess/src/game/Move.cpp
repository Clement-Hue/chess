#include "Move.h"
#include "Square.h"
#include "Piece.h"

/**
 * @param piece: the piece which moves.
 * @param square: the square that should be emptied
 */
static void remove_enemy_piece_if_exist(const Piece& piece,const Square& square) 
{
	if ( Piece* const piece_on_square = square.get_piece();
		piece_on_square && piece_on_square->is_enemy_of(piece))
	{
		piece_on_square->get_square()->remove_piece();
		piece_on_square->remove_square();
	}
}

static void move_piece_to_square(Piece& piece, Square& square) noexcept
{
	piece.get_square()->remove_piece();
	piece.set_square(square);
	square.set_piece(piece);
}

bool SimpleMove::operator()(Piece& piece, Square& square)
{
	remove_enemy_piece_if_exist(piece, square);
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

bool PromoteMove::operator()(Piece& pawn, Square& square)
{
	remove_enemy_piece_if_exist(pawn, square);
	this->color_.add_piece<Queen>(square);
	pawn.get_square()->remove_piece();
	this->color_.remove_piece(pawn);
	return true;
}

bool PawnDoubleMove::operator()(Piece& piece, Square& square)
{
	const auto pawn = dynamic_cast<Pawn*>(&piece);
	if (!pawn) return false;
	remove_enemy_piece_if_exist(*pawn, square);
	move_piece_to_square(*pawn, square);
	pawn->mark_as_moved();
	pawn->mark_as_double_moved();
	return true;
}

bool InPassingMove::operator()(Piece& piece, Square& square)
{
	move_piece_to_square(piece, square);
	remove_enemy_piece_if_exist(piece, *taken_pawn_.get_square());
	piece.mark_as_moved();
	return true;
}
