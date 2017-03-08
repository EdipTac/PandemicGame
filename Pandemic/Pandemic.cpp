// Pandemic - Build 1
//
//					Authors
//		============================
//		Michael Deom	-	29549641
//		Jonny Linton	-	
//		Edip Tac		-	
//		Kechun Ye		-	25654688
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
#include "Card.h"
#include "City.h"
#include "GameState.h"
#include "InfectionCard.h"
#include "InfectionCardDeck.h"
#include "Map.h"
#include "Menu.h"
#include "Player.h"
#include "PlayerCityCard.h"
#include "Serialization.h"
#include "Util.h"

void newGame();
void loadGame();
void waitForExit();
void performAction();
void driveOrFerry();
void directFlight();
void charterFlight();
void shuttleFlight();
void quit();
void showCity(std::unique_ptr<City>&);
void displayCities();
std::string solicitFileName();
City& solicitCity();
City& solicitConnection(const City& source);
std::string solicitPlayerName(const size_t number);
size_t solicitSize(size_t min, size_t max);

constexpr size_t minPlayers = 1;
constexpr size_t maxPlayers = 4;
constexpr size_t actionsPerTurn = 4;

std::unique_ptr<GameState> game;

const Menu mainMenu
{
	{
		{ "New Game",  newGame	},
		{ "Load Game", loadGame	},
		{ "Exit",	   quit		}
	}
};

const Menu turnMenu
{
	{
		{ "Perform Action",	performAction	},
		{ "Quit Game",		quit			}
	}
};

const Menu actionMenu
{
	{
		{ "Drive/Ferry",	driveOrFerry	},
		{ "Direct Flight",	directFlight	},
		{ "Charter Flight",	directFlight	},
		{ "Shuttle Flight",	shuttleFlight	},
		{ "Quit Game",		quit			}
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
	while (!game->shouldQuit() && actions > 0)
	{
		std::cout << "You have " << actions << " actions remaining.\n";
		actionMenu.solicitInput();
		--actions;
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

	const auto& newPosition = solicitConnection(position);
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

void charterFlight()
{
	auto& player = game->currentPlayer();
	auto& pawn = player.pawn();
	const auto& cards = player.cityCards();
	const auto& isPositionCard = [&pawn](const PlayerCityCard* card)
	{
		return card->city() == pawn.position();
	};

	if (!std::any_of(cards.begin(), cards.end(), isPositionCard))
	{
		std::cout << "You don't have any city cards that match your position.\n";
		return;
	}

	const auto& target = solicitCity();
	pawn.setPosition(target);
}

void shuttleFlight()
{
	if (!game->currentPlayer().pawn().position().hasResearchStation())
	{
		std::cout << "Your city does not have a research station.\n";
		return;
	}

	std::vector<City*> stations;

	for (const auto& city : game->map().cities())
	{
		if (city->hasResearchStation())
		{
			stations.push_back(city.get());
		}
	}

	if (stations.empty())
	{
		std::cout << "There are no other cities with research stations.\n";
		return;
	}


}

void quit()
{
	game->quit();
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

City& solicitCity()
{
	std::cout << "Where would you like to place your pawn? ";
	std::string cityName;
	while (true)
	{
		std::cin >> cityName;
		if (game->map().contains(cityName))
		{
			break;
		}
		std::cout << "No city of that name exists.\n";
	}
	return game->map().city(cityName);
}

City& solicitConnection(const City& source)
{
	std::cout << "Where would you like to move to? ";
	std::string targetName;
	City* target;
	while (true)
	{
		std::cin >> targetName;
		target = &game->map().city(targetName);
		if (game->map().contains(targetName) && source.isConnectedTo(*target))
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
void showCity(std::unique_ptr <City> const &city) {
	std::cout << city->name() << " Colour: " << colourAbbreviation(city->colour()) << "\n" <<
		"Infection status: " << "\n" << "Blue Cube: " << city->diseaseCubes(Colour::Blue) << "\n"
		"Black Cube: " << city->diseaseCubes(Colour::Black) << "\n" << "Red Cube: " << city->diseaseCubes(Colour::Red)
		<< "\n" << "Yellow Cube: " << city->diseaseCubes(Colour::Yellow) << "\n" << "Is quarantined: " << city->quarantined() << "\n"
		<< "Has research station ? " << city->hasResearchStation() << "\n" << "Outbreak status: \n" <<
		"Blue disease outbreak: " << city->diseaseOutbreak(Colour::Blue) << "\n"
		"Black disease outbreak: " << city->diseaseOutbreak(Colour::Black) << "\n" << "Red Cube: " << city->diseaseOutbreak(Colour::Red)
		<< "\n" << "Yellow Cube: " << city->diseaseOutbreak(Colour::Yellow) << std::endl;
}
void showCity(City* city) {
	std::cout << city->name() << " Colour: " << colourAbbreviation(city->colour()) << "\n" <<
		"Infection status: " << "\n" << "Blue Cube: " << city->diseaseCubes(Colour::Blue) << "\n"
		"Black Cube: " << city->diseaseCubes(Colour::Black) << "\n" << "Red Cube: " << city->diseaseCubes(Colour::Red)
		<< "\n" << "Yellow Cube: " << city->diseaseCubes(Colour::Yellow) << "\n" << "Is quarantined: " << city->quarantined() << "\n"
		<< "Has research station ? " << city->hasResearchStation() << "\n" << "Outbreak status: \n" <<
		"Blue disease outbreak: " << city->diseaseOutbreak(Colour::Blue) << "\n"
		"Black disease outbreak: " << city->diseaseOutbreak(Colour::Black) << "\n" << "Red Cube: " << city->diseaseOutbreak(Colour::Red)
		<< "\n" << "Yellow Cube: " << city->diseaseOutbreak(Colour::Yellow) << std::endl;
}


void displayCities() {
	auto& player = game->currentPlayer();
	const auto& position = player.pawn().position();
	std::cout << "You are currently in " << position.name() << "\n";
	while (true) {
		int index = 0;
		char op;
		
		std::cout <<"Press A,B,C,D to choose: \n" << "A) Dispaly all cities on the map " << "\n" << "B) Display specific city " << "\n"
			<< "C) See direct connection cities with your current city" << "\n"<< "D) Quit" <<"\n";
		std::cin >> op;
		if (op == 'A' || op == 'a') {
			for (const auto& city : game->map().cities())
			{
				std::cout << "City_Index_" << index << ":\n";
				showCity(city);
				index++;
			}
		}
		else if (op == 'B' || op == 'b') {
			
				std::string cityName;
				
				std::cout << "Which city do you want to see ? A) Input by city index number : B) Input by city name " << "\n";
				std::cin >> op;
				if (op == 'A' || op == 'a') {
					std::cin >> index;
					showCity(game->map().cities()[index]);
			     
				}
				else if (op == 'B' || op == 'b') {
					std::cin >> cityName;
					for (const auto& city : game->map().cities()) {
						if (iequals(city->name(),cityName)) {
							showCity(city);
						}
					}
				}

				std::cout << "Do you want see the direct connnections of this city (Y/N) " << "\n";
				std::cin >> op;

				if(op == 'Y' || op == 'y') {
					for (const auto& city : game->map().cities()[index]->connections())
					{
						showCity(city);
						
					}
				}


		}
		else if (op == 'C' || op == 'c') {

			std::cout << "In one action, you can move to\n";
			for (const auto& city : position.connections())
			{
				showCity(city);
			}

		}
		else if (op == 'D' || op == 'd') {
			break;
		}

	}
	
}

bool iequals(const std::string& a, const std::string& b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}
