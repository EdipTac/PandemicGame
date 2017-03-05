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

//// Project file inclusions
//#include "Card.h"
//#include "City.h"
//#include "GameState.h"
//#include "Player.h"
//#include "Map.h"

#include "InfectionCardDeck.h"
//#include "Serialization.h"

//  ----    Constant definitions    ----
constexpr size_t numPlayers = 2;		// Number of players in the game.
constexpr size_t startingHandSize = 4;	// Number of player cards each player receives.

//static const std::vector<Card> roleCards	// Role cards in the game. To be expanded later.
//{
//	{ "Contingency Planner",	"Take an event card from the discard pile."		},
//	{ "Dispatcher",				"Move any pawn to any city with another pawn."	}
//};


//  ----    Function forward declarations    ----

//// Solicits a file name and returns the map stored in the text file
//Map loadMapFile();
//
//// Gets a file name from the player to load a map from
//std::string solicitFileName();
//
//// Creates city cards from loaded cities
//std::vector<Card> populatePlayerCards(const Map& map, const size_t number);
//
//// Prints the cities belonging to a map
//void listCities(const Map& map);
//
//// Gets a player name from the user
//std::string solicitPlayerName(const size_t number);
//
//// Gives a role card to a player
//void distributeRoleCard(Player& player, const size_t playerNumber);
//
//// Gives player cards to a player
//void distributePlayerCards(Player& player, std::vector<Card>& playerCards);
//
//// Gets a city name from the user
//City& solicitCity(const Map& map);


//	----    Program entry point    ----
void main()
{
	// Title display
	std::cout << "    --------    P A N D E M I C    --------\n\n\n";

	//// Setup - Solicit map file name and load map, generate player cards from map, and print list of cities
	//GameState game;
	//game.setMap(std::make_unique<Map>(loadMapFile()));
	//auto& map = game.map();

	//auto playerCards = populatePlayerCards(map, numPlayers * startingHandSize);
	//listCities(map);

	//// Construct players
	//for (auto i = 1; i <= numPlayers; ++i)
	//{
	//	auto player = std::make_unique<Player>(solicitPlayerName(i), map);	// Get names and construct players
	//	distributeRoleCard(*player, i);										// Attach role card
	//	distributePlayerCards(*player, playerCards);						// Give player cards
	//	player->pawn().position(solicitCity(map));							// Solicit city name and place pawn
	//	std::cout << "Your pawn is in " << player->pawn().position().name() << ".\n\n";
	//	game.addPlayer(std::move(player));
	//}

	//// Save game
	//std::string saveFileName;
	//while (true)
	//{
	//	std::cout << "Where do you wish to save this game file? ";
	//	std::getline(std::cin >> std::ws, saveFileName);
	//	if (fileExists(saveFileName))
	//	{
	//		std::cout << "File already exists. Overwrite? (y/n): ";
	//		std::string overwriteResponse;
	//		std::getline(std::cin >> std::ws, overwriteResponse);
	//		std::transform(overwriteResponse.begin(), overwriteResponse.end(), overwriteResponse.begin(), ::tolower);
	//		if (overwriteResponse == "y")
	//		{
	//			break;
	//		}
	//	}
	//}
	//
	//writeMapToFile(map, saveFileName);
	//std::cout << "Game saved as " << saveFileName << "\nThanks for playing!" << std::endl;
	//initiate an infectionCardDeck
	InfectionCardDeck infectionDeck();


}

//std::vector<Card> populatePlayerCards(const Map& map, const size_t number)
//{
//	const auto& cities = map.cities();
//	std::mt19937 gen { std::random_device{}() };
//	std::uniform_int_distribution<> dis(0, cities.size() - 1);
//	std::vector<Card> playerCards;
//	for (size_t i = 1; i <= number; ++i)
//	{
//		playerCards.push_back({ cities[dis(gen)]->name(), "City card" });
//	}
//	return playerCards;
//}
//
//std::string solicitFileName()
//{
//	std::string fileName;
//	while (true)
//	{
//		std::cout << "Load map file to start new game: ";
//		std::cin >> fileName;
//		if (fileExists(fileName))
//		{
//			break;
//		}
//		std::cout << "File not found.\n";
//	}
//	return fileName;
//}
//
//Map loadMapFile()
//{
//	const auto fileName = solicitFileName();
//	std::cout << "\nLoading map \"" << fileName << "\"...\n";
//	auto map = readMapFromFile(fileName);
//	std::cout << "Map \"" << fileName << "\" loaded!\n\n";
//	return map;
//}
//
//void listCities(const Map& map)
//{
//	std::cout << "Cities of " << map.name() << ": \n";
//	for (const auto& city : map.cities())
//	{
//		std::cout << "    " << city->name() << "\n";
//	}
//	std::cout << "\n";
//}
//
//City& solicitCity(const Map& map)
//{
//	std::cout << "Where would you like to place your pawn? ";
//	std::string cityName;
//	while (true)
//	{
//		std::cin >> cityName;
//		if (map.contains(cityName))
//		{
//			break;
//		}
//		std::cout << "No city of that name exists.\n";
//	}
//	return map.city(cityName);
//}
//
//std::string solicitPlayerName(const size_t number)
//{
//	std::cout << "Enter the name of player " << number << ": ";
//	std::string playerName;
//	while (true)
//	{
//		std::getline(std::cin >> std::ws, playerName);
//		if (!playerName.empty())
//		{
//			break;
//		}
//		std::cout << "Player name cannot be empty.\n";
//	}
//	std::cout << "Welcome, " << playerName << "\n\n";
//	return playerName;
//}
//
//void distributeRoleCard(Player& player, const size_t number)
//{
//	player.roleCard(std::make_unique<Card>(roleCards[number - 1]));
//	std::cout << "You have been given the following role: " << player.roleCard().name() << "\n";
//	std::cout << "\tDescription: " << player.roleCard().description() << "\n\n";
//}
//
//void distributePlayerCards(Player& player, std::vector<Card>& playerCards)
//{
//	for (auto i = 1; i <= startingHandSize; ++i)
//	{
//		if (playerCards.empty())
//		{
//			break;
//		}
//		player.hand().add(std::make_unique<Card>(playerCards.back()));
//		playerCards.pop_back();
//	}
//
//	std::cout << "You have received the following player cards:\n";
//	for (const auto& card : player.hand().cards())
//	{
//		std::cout << "\t" << card->name() << "\n";
//	}
//	std::cout << "\n";
//}
