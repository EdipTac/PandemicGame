#include "CityCard.h"

CityCard::CityCard()
{}

CityCard::CityCard(City city)
	:_city(city) {}

City CityCard::city() const
{
	return this->_city;
}

void CityCard::setCity(const City city)
{
	this->_city = city;
}
