#pragma warning(disable : 4100)	// To be removed

#include "PlayerCityCard.h"

// Default Constructor
//PlayerCityCard::PlayerCityCard()
//	: PlayerCard() {}

PlayerCityCard::PlayerCityCard()
	: CityCard {}
{}

// Constructor
PlayerCityCard::PlayerCityCard(City& city)
	: CityCard { city }
{}

PlayerCityCard::~PlayerCityCard() {}


// Custom implementation of the inherited virtual function from PlayerCard
std::string PlayerCityCard::toString()
{
	return "Type: PlayerCityCard, " + PlayerCard::toString();
}

std::string PlayerCityCard::name() const
{
	return CityCard::name();
}

std::string PlayerCityCard::description() const
{
	return CityCard::description();
}

void PlayerCityCard::cardWork(Deck<InfectionCard>& deck) {}

void PlayerCityCard::onDraw(Board& state) {}

PlayerCardType PlayerCityCard::type() const
{
	return PlayerCardType::CityCard;
}
