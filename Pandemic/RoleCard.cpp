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
	: _role{ "" }, _description{ "" }, _color{ "" }
{

}

RoleCard::RoleCard(std::string role, std::string description, std::string color)
	: _role( role ), _description( description ), _color( color )
{
	
}

void RoleCard::printRole() {
	std::cout << _role << std::endl << _color << std::endl << _description << std::endl;
}
