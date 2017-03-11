#include <string>
#include <iostream>
#include "RoleCard.h"


/* 
This is the cpp file for the role card. The code makes use of the 2 constructors for the RoleCards
where the specific constructor makes it more space efficient in writing out the code during the
card's initialization process. The printRole function is there in order to display the role of the player
during the game. Each of the cards have their specific role (name) the description of each role, as well as
the color corresponding to each role that will be used to decide on the color of the pawn for that character.
*/
RoleCard::RoleCard()
	: TextualCard { "", ""}
	, _color { "" }
{

}

RoleCard::RoleCard(const std::string& role, const std::string& description, const std::string& color)
	: TextualCard { role, description }
	, _color { color }
{
	
}

RoleCard::~RoleCard() {}

void RoleCard::printRole() {
	std::cout << name() << std::endl << _color << std::endl << description() << std::endl;
}

void RoleCard::onDraw(GameState& state) {}
