#include "PlayerCard.h"

PlayerCard::PlayerCard()
	: _name("") {}

PlayerCard::PlayerCard(std::string name)
	: _name(name) {}

std::string PlayerCard::getName() const
{
	return _name;
}

void PlayerCard::setName(const std::string name)
{
	this->_name = name;
}

PCCity::PCCity()
	: PlayerCard() {}

PCCity::PCCity(std::string name)
	: PlayerCard(name) {}

PCEvent::PCEvent()
	: PlayerCard(), _description("") {}

PCEvent::PCEvent(std::string name, std::string description)
	: PlayerCard(name), _description(description) {}

std::string PCEvent::getDescription() const
{
	return _description;
}

void PCEvent::setDescription(const std::string description)
{
	this->_description = description;
}

PCEpidemic::PCEpidemic()
	: PlayerCard("EPIDEMIC") {}

std::string PCEpidemic::getDescription() const
{
	return EPIDEMIC_DESCRIPTION;
}
