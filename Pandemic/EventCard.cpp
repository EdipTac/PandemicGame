#include "EventCard.h"

// Default Constructor
//Event::Event()
//	: PlayerCard(), _description("") {}

// Constructor
EventCard::EventCard(std::string name, std::string description)
	: PlayerCard(), _description(description) {}

std::string EventCard::name() const
{
	return _name;
}

// Accessor for _description
std::string EventCard::description() const
{
	return _description;
}

// Mutator for _description
void EventCard::setDescription(const std::string description)
{
	_description = description;
}

// Custom implementation of the inherited virtual function from PlayerCard
std::string EventCard::toString()
{
	return "Event\n" + PlayerCard::toString() + ", Description: " + _description;
}