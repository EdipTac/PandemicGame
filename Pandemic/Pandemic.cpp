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

#pragma warning (disable: 4592)	// Static initialization warning

//  ----    Inclusions    ----  //
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
#include "Serialization.h"

void newGame();
void loadGame();
void waitForExit();
std::string solicitFileName();
Map loadMapFile();
City& solicitCity(const Map& map);
std::string solicitPlayerName(const size_t number);

static const Menu mainMenu
{
	{
		{ "New Game",  newGame },
		{ "Load Game", loadGame },
		{ "Exit",      waitForExit }
	}
};

//	----    Program entry point    ----  //
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
	solicitFileName();
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

std::string solicitFileName()
{
	std::string fileName;
	while (true)
	{
		std::cout << "Load map file to start new game: ";
		std::cin >> fileName;
		if (fileExists(fileName))
		{
			break;
		}
		std::cout << "File not found.\n";
	}
	return fileName;
}

Map loadMapFile()
{
	const auto fileName = solicitFileName();
	std::cout << "\nLoading map \"" << fileName << "\"...\n";
	auto map = readMapFromFile(fileName);
	std::cout << "Map \"" << fileName << "\" loaded!\n\n";
	return map;
}

City& solicitCity(const Map& map)
{
	std::cout << "Where would you like to place your pawn? ";
	std::string cityName;
	while (true)
	{
		std::cin >> cityName;
		if (map.contains(cityName))
		{
			break;
		}
		std::cout << "No city of that name exists.\n";
	}
	return map.city(cityName);
}

std::string solicitPlayerName(const size_t number)
{
	std::cout << "Enter the name of player " << number << ": ";
	std::string playerName;
	while (true)
	{
		std::getline(std::cin >> std::ws, playerName);
		if (!playerName.empty())
		{
			break;
		}
		std::cout << "Player name cannot be empty.\n";
	}
	std::cout << "Welcome, " << playerName << "\n\n";
	return playerName;
}
