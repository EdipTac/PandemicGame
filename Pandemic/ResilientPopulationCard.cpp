#include "ResilientPopulationCard.h"
#include <memory>

using namespace action;

ResilientPopulationCard::ResilientPopulationCard() : EventCard{ "Resilient Population", "Take a card from the Infection Discard Pile and remove it from the game.", std::make_unique<action::ResilientPopulation>(action::ResilientPopulation()) } {}