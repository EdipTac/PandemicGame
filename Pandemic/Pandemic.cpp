// Pandemic - Build 1
//
//					Authors
//		============================
//		Michael Deom	-	29549641
//		Jonny Linton	-	
//		Edip Tac		-	
//		Kechun Ye		-	
//
// Submitted 15/03/2017
//
// Build 1 of project.
//
// An implementation of the board game "Pandemic" by Z-Man Games.

#pragma warning (disable: 4592)

//  ----    Inclusions    ----
// Standard library inclusions
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// Project file inclusions
//#include "Card.h"
#include "City.h"
#include "GameState.h"
#include "Player.h"
#include "Map.h"
#include "Menu.h"
#include "Serialization.h"
#include "Util.h"
#include "InfectionCard.h"
#include "InfectionCardDeck.h"
//#include "Serialization.h"

void newGame();
void loadGame();
void waitForExit();

static const Menu mainMenu
{
	{
		{ "New Game",  newGame },
		{ "Load Game", loadGame },
		{ "Exit",      waitForExit }
	}
};

//	----    Program entry point    ----
void main()
{
	readMapFromFile("earth.map");
	// Title display
	std::cout << "    --------    P A N D E M I C    --------    \n\n\n";
	mainMenu.solicitInput();
}

void newGame()
{
	std::cout << "New game...\n";
}

void loadGame()
{
	std::cout << "Load game...\n";
}

void waitForExit()
{
	std::cout << "Press any key to continue...\n";
	std::cin.get();
}
