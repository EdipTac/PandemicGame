#include "Event.h"

// Default Constructor
Event::Event()
	: PlayerCard(), _description("") {}

// Constructor
Event::Event(std::string name, std::string description)
	: PlayerCard(name), _description(description) {}

// Accessor for _description
std::string Event::description() const
{
	return _description;
}

// Mutator for _description
void Event::setDescription(const std::string description)
{
	this->_description = description;
}

// Custom implementation of the inherited virtual function from PlayerCard
std::string Event::toString()
{
	return "Event\n" + PlayerCard::toString() + ", Description: " + _description;
}