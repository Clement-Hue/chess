#include "PawnColorVisitor.h"

void PawnPseudoLegalSquares::visit(BlackColor& color) const
{
	this->add_file_eligible_squares<BlackColor>(color);
	this->add_takeable_squares<BlackColor>(color);
}

void PawnPseudoLegalSquares::visit(WhiteColor& color) const
{
	this->add_file_eligible_squares<WhiteColor>(color);
	this->add_takeable_squares<WhiteColor>(color);
}

void PawnLegalSquares::visit(BlackColor& color) const
{
	this->remove_not_legal_takeable_squares<BlackColor>(color);
}

void PawnLegalSquares::visit(WhiteColor& color) const
{
	this->remove_not_legal_takeable_squares<WhiteColor>(color);
}
