#include "PlayerCard.h"

// Default Constructor
PlayerCard::PlayerCard()
	: _name("") {}

// Constructor
PlayerCard::PlayerCard(std::string name)
	: _name(name) {}

// Accessor for _name
std::string PlayerCard::name() const
{
	return _name;
}

// Mutator for _name
void PlayerCard::setName(const std::string name)
{
	this->_name = name;
}

// virtual function that converts a PlayerCard object into an informative string.
std::string PlayerCard::toString()
{
	return "Name: " +_name;
}

// Default Constructor
PCCity::PCCity()
	: PlayerCard() {}

// Constructor
PCCity::PCCity(std::string name)
	: PlayerCard(name) {}

// Custom implementation of the inherited virtual function from PlayerCard
std::string PCCity::toString()
{
	return "PCCity\n" + PlayerCard::toString();
}

// Default Constructor
PCEvent::PCEvent()
	: PlayerCard(), _description("") {}

// Constructor
PCEvent::PCEvent(std::string name, std::string description)
	: PlayerCard(name), _description(description) {}

// Accessor for _description
std::string PCEvent::description() const
{
	return _description;
}

// Mutator for _description
void PCEvent::setDescription(const std::string description)
{
	this->_description = description;
}

// Custom implementation of the inherited virtual function from PlayerCard
std::string PCEvent::toString()
{
	return "PCEvent\n" + PlayerCard::toString() + ", Description: " + _description;
}

// Default Constructor
PCEpidemic::PCEpidemic()
	: PlayerCard("EPIDEMIC") {}

// Accessor for EPIDEMIC_DESCRIPTION
std::string PCEpidemic::getDescription() const
{
	return EPIDEMIC_DESCRIPTION;
}

// Custom implementation of the inherited virtual function from PlayerCard
std::string PCEpidemic::toString()
{
	return "PCEpidemic\n" + PlayerCard::toString() + ", Description: \n" + EPIDEMIC_DESCRIPTION;
}
