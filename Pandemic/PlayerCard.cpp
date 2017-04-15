#include "PlayerCard.h"

PlayerCard::~PlayerCard() {}

bool PlayerCard::isCityCard() const
{
	return false;
}

bool PlayerCard::isEventCard() const
{
	return false;
}

bool PlayerCard::isEpidemicCard() const
{
	return false;
}

bool PlayerCard::isHandCard() const
{
	return isCityCard() || isEventCard();
}

std::string PlayerCard::toString()
{
	return "Name: " + name();
}
