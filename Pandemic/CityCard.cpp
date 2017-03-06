#include "City.h"
#include "CityCard.h"



CityCard::CityCard(City& city)
	: _city{ city }
{}

CityCard::~CityCard() {}

City& CityCard::city() const
{
	return _city;
}

std::string CityCard::name() const
{
	return _city.name();
}

std::string CityCard::description() const
{
	return "City card";
}

Colour CityCard::colour() const
{
	return _city.colour();
}
