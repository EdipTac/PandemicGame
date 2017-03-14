#include "PlayerCard.h"

PlayerCard::~PlayerCard() {}

bool PlayerCard::isCityCard() const
{   
	return false;
}

std::string PlayerCard::toString()
{
	return "Name: " + name();
}
