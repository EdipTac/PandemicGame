#include "ForecastCard.h"
#include <memory>

using namespace action;

ForecastCard::ForecastCard() : EventCard{ "Forecast", "Examine the top 6 cards of the Infection Draw Pile, rearrange them in the order of your choice, then place them back on the pile", std::make_unique<action::Forecast>(action::Forecast()) }{}