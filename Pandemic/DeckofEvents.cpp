#include <string>
#include <vector>

#include "DeckOfEvents.h"

#include "AirliftCard.h"
#include "OneQuietNightCard.h"
#include "ResilientPopulationCard.h"
#include "GovernmentGrantCard.h"
#include "ForecastCard.h"

std::vector<std::unique_ptr<EventCard>> event::cards()
{
	std::vector<std::unique_ptr<EventCard>> v;
	v.push_back(std::make_unique<AirliftCard>());
	v.push_back(std::make_unique<OneQuietNightCard>());
	v.push_back(std::make_unique<ResilientPopulationCard>());
	v.push_back(std::make_unique<GovernmentGrantCard>());
	v.push_back(std::make_unique<ForecastCard>());
	return v;
}
