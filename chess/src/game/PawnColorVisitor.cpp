#include "PawnColorVisitor.h"

void PawnPseudoLegalSquares::visit(BlackColor&) const
{
	this->add_file_eligible_squares<BlackColor>();
	this->add_takeable_squares<BlackColor>();
}

void PawnPseudoLegalSquares::visit(WhiteColor&) const
{
	this->add_file_eligible_squares<WhiteColor>();
	this->add_takeable_squares<WhiteColor>();
}

void PawnLegalTakeableSquares::visit(BlackColor& color) const
{
	this->remove_not_legal_takeable_squares<BlackColor>();
}

void PawnLegalTakeableSquares::visit(WhiteColor& color) const
{
	this->remove_not_legal_takeable_squares<WhiteColor>();
}
