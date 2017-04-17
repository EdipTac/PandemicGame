#include "PlayerCityCard.h"
#include "Util.h"

PlayerCityCard::PlayerCityCard()
	: CityCard {}
{}

// Constructor
PlayerCityCard::PlayerCityCard(City& city)
	: CityCard { city }
{}

PlayerCityCard::~PlayerCityCard() {}

// Custom implementation of the inherited virtual function from PlayerCard
std::string PlayerCityCard::string(const size_t spacing) const
{
	return rawString() + spaces(spacing) + " [City Card]";
}

std::string PlayerCityCard::rawString() const
{
	return name() + " (" + colourName(colour()) + ")";
}

std::string PlayerCityCard::name() const
{
	return CityCard::name();
}

std::string PlayerCityCard::description() const
{
	return CityCard::description();
}

void PlayerCityCard::cardWork(Deck<InfectionCard>&) {}

void PlayerCityCard::onDraw() {}

PlayerCardType PlayerCityCard::type() const
{
	return PlayerCardType::CityCard;
}
