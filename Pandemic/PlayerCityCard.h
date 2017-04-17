#pragma once

#include "City.h"
#include "PlayerCard.h"
#include "CityCard.h"
#include <string>

// PlayerCityCard class - represents PlayerCards of type City.
class PlayerCityCard
	: public PlayerCard
	, public CityCard
{
public:
	PlayerCityCard();
	// Constructs a city player card for a given city
	PlayerCityCard(City& city);

	// Destructor
	~PlayerCityCard() override;

	// Custom implementation of the inherited virtual function from PlayerCard
	virtual std::string string(const size_t spacing = 0) const override;
	virtual std::string rawString() const override;

	// Inherited via PlayerCard
	virtual std::string name() const override;
	virtual std::string description() const override;

	virtual void cardWork(Deck<InfectionCard>& deck) override;

	void onDraw() override;

	virtual PlayerCardType type() const override;
};