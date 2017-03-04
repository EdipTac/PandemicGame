// Pandemic - Build 1
//
// Authors
//		Michael Deom	-	29549641
//		Jonny Linton	-	
//		Edip Tac		-	
//		Kechun Ye		-	
//
// Submitted 10/03/2017
//
// Build 1 of project.
//
// An implementation of the board game "Pandemic" by Z-Man Games.

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
#include "InfectionCard.h"
#include "InfectionCardDeck.h"
//#include "Serialization.h"

void waitForExit();

//	----    Program entry point    ----
void main()
{
	// Title display
	std::cout << "    --------    P A N D E M I C    --------    \n\n\n";
	std::cout << "Please select an option:\n";
	std::cout << "\t(1) New Game\n";
	std::cout << "\t(2) Load Game\n";
	std::cout << "\t(3) Exit\n";
	waitForExit();
}

void waitForExit()
{
	std::cout << "Press any key to continue...\n";
	getchar();
}