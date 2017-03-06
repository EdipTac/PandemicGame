#include "EventCard.h"

// Default Constructor
//Event::Event()
//	: PlayerCard(), _description("") {}

// Constructor
EventCard::EventCard(std::string name, std::string description)
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

// Custom implementation of the inherited virtual function from PlayerCard
std::string EventCard::toString()
{
	return "Event\n" + PlayerCard::toString() + ", Description: " + description();
}