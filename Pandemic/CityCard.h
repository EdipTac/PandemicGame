#pragma once

#include <string>

#include "Card.h"
#include "Colour.h"
#include "City.h"

class CityCard
	: Card
{
public:
	CityCard(City& city);
	virtual ~CityCard() override;
	City& city() const;
	std::string name() const override;
	std::string description() const override;
	Colour colour() const;

private:
	City& _city;
};
