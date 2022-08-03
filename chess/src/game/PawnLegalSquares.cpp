#include "PawnLegalSquares.h"

void PawnLegalSquares::visit(BlackColor& color) const
{
	this->add_file_legal_squares<BlackColor>(color);
	this->add_takeable_squares<BlackColor>(color);
	this->add_in_passing_move_if_possible<BlackColor>(color);
}

void PawnLegalSquares::visit(WhiteColor& color) const
{
	this->add_file_legal_squares<WhiteColor>(color);
	this->add_takeable_squares<WhiteColor>(color);
	this->add_in_passing_move_if_possible<WhiteColor>(color);
}

