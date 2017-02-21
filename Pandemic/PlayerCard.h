#pragma once

/*
Distinct Part 3 – Player cards classes:
Implement a C++ classes that represents the various 
player cards : City cards, Epidemic cards and Event
cards, with their characteristics.

Write a driver program that instantiates two players
with different player cards, and demonstrate how the
player’s cards affect the players’ action.
*/

#include <string>
#include <iostream>


class PlayerCard {
private:
	std::string _name;

public:
	PlayerCard();
	PlayerCard(std::string name);

	std::string getName() const;
	void setName(const std::string name);

	virtual std::string toString();
};

class PCCity : public PlayerCard {
public:
	PCCity();
	PCCity(std::string name); 
	std::string toString();
};

class PCEvent : public PlayerCard {
private:
	std::string _description;
public:
	PCEvent();
	PCEvent(std::string name, std::string description);

	std::string getDescription() const;
	void setDescription(const std::string description);
	std::string toString();
};

class PCEpidemic : public PlayerCard {
private:
	const std::string EPIDEMIC_DESCRIPTION = "1-Increase:\nMove the infection rate marker forward 1 space\n2-Infect:\nDraw the bottom card from the infection deck and put 3 cubes on that city. Discard that card\n3-Intensify:\nShuffle the cards in the infection discard pile and put them on top of the infection deck.\n\n";
public:
	PCEpidemic();

	std::string getDescription() const;
	std::string toString();
};