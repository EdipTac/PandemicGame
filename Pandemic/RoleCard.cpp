//#pragma warning(disable : 4100)	// To be removed

#include <string>
#include <iostream>

#include "Board.h"
#include "RoleCard.h"
#include "City.h"

/* 
This is the cpp file for the role card. The code makes use of the 2 constructors for the RoleCards
where the specific constructor makes it more space efficient in writing out the code during the
card's initialization process. The printRole function is there in order to display the role of the player
during the game. Each of the cards have their specific role (name) the description of each role, as well as
the color corresponding to each role that will be used to decide on the color of the pawn for that character.
*/

RoleCard::RoleCard(const std::string& role, const std::string& description, const std::string& color)
	: TextualCard { role, description }
	, _color { color }
{}

RoleCard::~RoleCard() {}

void RoleCard::print() const
{
	std::cout << name() << " (" << _color << ")\n" << description() << "\n";
}

void RoleCard::onDraw() {}

std::vector<action::Action*> RoleCard::actions() const
{
	std::vector<action::Action*> list;
	for (const auto& action : _actions)
	{
		list.push_back(action.get());
	}
	return list;
}

int RoleCard::numCardsNeededToCure() const{
	return 5;
}

void RoleCard::treatDisease(City& city, const Colour& colour) const
{
	city.removeDiseaseCubes(colour, 1, Board::instance().cubePool());
}

void RoleCard::onEnter(City&) const {}

void RoleCard::onExit(City&) const {}
