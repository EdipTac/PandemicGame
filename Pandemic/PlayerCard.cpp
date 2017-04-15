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

std::string PlayerCard::toString()
{
	return "Name: " + name();
}
void PlayerCard::cardWork(Deck<InfectionCard>& deck){}
