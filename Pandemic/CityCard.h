#pragma once

#include <string>

#include "Card.h"
#include "Colour.h"

class City;

// Represents a card that references a city.
class CityCard
	: public Card
{
public:
	CityCard();

	// Constructs a card referencing a given city
	CityCard(City& city);

	// Destructor
	virtual ~CityCard() override;

	// The referenced city
	City& city() const;

	// The name of the referenced city
	std::string name() const override;

	// The card's description
	virtual std::string description() const override;

	// The colour of the referenced city
	Colour colour() const;

private:
	City* _city;
};
