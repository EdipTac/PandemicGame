#include "PlayerCard.h"

PlayerCard::PlayerCard()
	: _name("") {}

PlayerCard::PlayerCard(std::string name)
	: _name(name) {}

//PlayerCard::PlayerCard(const PlayerCard& playercard)
//	:_name("") {}

std::string PlayerCard::getName() const
{
	return _name;
}

void PlayerCard::setName(const std::string name)
{
	this->_name = name;
}

std::string PlayerCard::toString()
{
	return "Name: " +_name;
}

PCCity::PCCity()
	: PlayerCard() {}

PCCity::PCCity(std::string name)
	: PlayerCard(name) {}

std::string PCCity::toString()
{
	return "PCCity\n" + PlayerCard::toString();
}

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

std::string PCEvent::toString()
{
	return "PCEvent\n" + PlayerCard::toString() + ", Description: " + _description;
}

PCEpidemic::PCEpidemic()
	: PlayerCard("EPIDEMIC") {}

std::string PCEpidemic::getDescription() const
{
	return EPIDEMIC_DESCRIPTION;
}

std::string PCEpidemic::toString()
{
	return "PCEpidemic\n" + PlayerCard::toString() + ", Description: \n" + EPIDEMIC_DESCRIPTION;
}
