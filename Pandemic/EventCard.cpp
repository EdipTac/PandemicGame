#include "EventCard.h"

// Constructor
EventCard::EventCard(const std::string& name, const std::string& description)
	: TextualCard { name, description }
{}

EventCard::~EventCard() {}

std::string EventCard::name() const
{
	return TextualCard::name();
}

std::string EventCard::description() const
{
	return TextualCard::name();
}

std::string EventCard::toString()
{
	return "Event\n" + PlayerCard::toString() + ", Description: " + description();
}

void EventCard::onDraw(GameState& state) {}
