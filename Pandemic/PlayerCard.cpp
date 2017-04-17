#include "PlayerCard.h"

PlayerCard::~PlayerCard() {}

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
	return type() == PlayerCardType::CityCard
		|| type() == PlayerCardType::EventCard;
}
