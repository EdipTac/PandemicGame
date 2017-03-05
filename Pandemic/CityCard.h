#pragma once
#include "Card.h"
#include "City.h"

class CityCard : Card {
private:
	City _city;
public:
	CityCard();
	CityCard(City city);

	City city() const;
	void setCity(const City city);
};