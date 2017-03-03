#pragma once
#include <string>

/*
This is the header file for the RoleCards that will be used in the game that indicate the
role of each character within the game, the description of what their roles can do, and also
a specific color corresponding to each role that will determine the color of the pawn that each
character will make use of. 
The code consists of the default and specific constructors.
Additionally, the code also consists of a printRole function that displays the content
of the role cards, i.e, their Name, Color, and Description.
*/


class RoleCard{
private:
	std::string _role;
	std::string _description;
	std::string _color;
public:
	RoleCard();
	RoleCard(std::string role, std::string description, std::string color);


	void printRole();
};