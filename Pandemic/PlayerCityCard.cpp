#include "PlayerCityCard.h"

// Default Constructor
//PlayerCityCard::PlayerCityCard()
//	: PlayerCard() {}

// Constructor
PlayerCityCard::PlayerCityCard(City& city)
	: CityCard { city }
{}

PlayerCityCard::~PlayerCityCard() {}

bool PlayerCityCard::isCityCard() const
{
	return true;
}

// Custom implementation of the inherited virtual function from PlayerCard
std::string PlayerCityCard::toString()
{
	return "PlayerCityCard\n" + PlayerCard::toString();
}

std::string PlayerCityCard::name() const
{
	return CityCard::name();
}

std::string PlayerCityCard::description() const
{
	return CityCard::description();
}
