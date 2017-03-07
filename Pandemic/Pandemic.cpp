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

// Disable static initialization warning
#pragma warning (disable: 4592)

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
#include "PlayerCityCard.h"
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
void performAction();
void driveOrFerry();
void directFlight();
std::string solicitFileName();
City& solicitCity(const Map& map);
City& solicitConnection(const Map& map, const City& source);
std::string solicitPlayerName(const size_t number);
size_t solicitSize(size_t min, size_t max);

constexpr size_t minPlayers = 1;
constexpr size_t maxPlayers = 4;
constexpr size_t actionsPerTurn = 4;

std::unique_ptr<GameState> game;

const auto& noOp = [](){};

const Menu mainMenu
{
	{
		{ "New Game",  newGame	},
		{ "Load Game", loadGame	},
		{ "Exit",	   noOp		}
	}
};

const Menu turnMenu
{
	{
		{ "Perform Action",	performAction		   },
		{ "Quit Game",		[]() { game->quit(); } }
	}
};

const Menu actionMenu
{
	{
		{ "Drive/Ferry",	driveOrFerry			},
		{ "Direct Flight",	directFlight			},
		{ "Quit Game",		[]() { game->quit(); }	}
	}
};

//	----    Program entry point    ----  //
void main()
{
	// Title display
	std::cout << "    --------    P A N D E M I C    --------    \n\n\n";
	mainMenu.solicitInput();

	while (!game->shouldQuit())
	{
		auto& currentPlayer = game->nextPlayer();
		std::cout << currentPlayer.name() << "'s turn.\n";
		turnMenu.solicitInput();
	}

	waitForExit();
}

void newGame()
{
	std::cout << "\n    --------    N E W   G A M E    --------    \n\n";

	game = std::make_unique<GameState>();

	const auto& fileName = solicitFileName();
	std::cout << "\nLoading map \"" << fileName << "\"...\n";
	game->setMap(readMapFromFile(fileName));
	std::cout << "Map \"" << fileName << "\" loaded!\n\n";

	std::cout << "How many players? ";
	const auto& numPlayers = solicitSize(minPlayers, maxPlayers);
	const auto& map = game->map();
	for (auto i = 1; i <= numPlayers; ++i)
	{
		const auto& playerName = solicitPlayerName(i);
		auto player = std::make_unique<Player>();
		player->setName(playerName);
		player->pawn().setPosition(map.startingCity());
		game->addPlayer(std::move(player));
	}
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

void performAction()
{
	auto actions = actionsPerTurn;
	std::cout << "You have " << actions << " actions remaining.\n";
	while (!game->shouldQuit() && actions > 0)
	{
		--actions;
		actionMenu.solicitInput();
	}
}

void driveOrFerry()
{
	auto& player = game->currentPlayer();
	
	const auto& position = player.pawn().position();
	std::cout << "You are currently in " << position.name() << "\n";
	std::cout << "You can move to\n";
	for (const auto& connection : position.connections())
	{
		std::cout << "\t" << connection->name() << "\n";
	}

	const auto& newPosition = solicitConnection(game->map(), position);
	player.pawn().setPosition(newPosition);
}

void directFlight()
{
	const auto& cards = game->currentPlayer().cityCards();
	
	if (cards.empty())
	{
		std::cout << "You have no city cards.\n";
		return;
	}

	std::cout << "City cards: \n";
	for (const auto& card : cards)
	{
		std::cout << "\t" << card->name() << "\n";
	}
}

std::string solicitFileName()
{
	std::string fileName;
	while (true)
	{
		std::cout << "Load map file to start new game: ";
		std::cin >> fileName;
		std::cin.get();
		if (fileExists(fileName))
		{
			break;
		}
		std::cout << "File not found.\n";
	}
	return fileName;
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

City& solicitConnection(const Map& map, const City& source)
{
	std::cout << "Where would you like to move to? ";
	std::string targetName;
	City* target;
	while (true)
	{
		std::cin >> targetName;
		target = &map.city(targetName);
		if (map.contains(targetName) && source.isConnectedTo(*target))
		{
			break;
		}
		std::cout << "No city of that name connected to " << targetName << ".\n";
	}
	return *target;
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
	//std::cout << "Welcome, " << playerName << "\n\n";
	return playerName;
}

size_t solicitSize(size_t min, size_t max)
{
	size_t size;
	while (true)
	{
		std::cout << "Enter a number from " << min << " to " << max << ", inclusive: ";
		std::cin >> size;
		std::cin.get();
		if (min <= size && size <= max)
		{
			break;
		}
		std::cout << "Not a valid number.\n";
	}
	return size;
}
