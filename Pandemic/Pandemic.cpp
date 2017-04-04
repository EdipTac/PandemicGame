//  Pandemic - Build 1
//
//					Authors
//		============================
//		Michael Deom	-	29549641
//		Jonny Linton	-	
//		Edip Tac		-	
//		Kechun Ye		-	25654688
//
//  Submitted 15/03/2017
//
//  Build 1 of project.
//
//  An implementation of the board game "Pandemic" by Z-Man Games.

#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "ActionController.h"
#include "Card.h"
#include "City.h"
#include "DeckofEvents.h"
#include "DeckofRoles.h"
#include "Dispatcher.h"
#include "DriveOrFerry.h"
#include "EventCard.h"
#include "Board.h"
#include "InfectionCard.h"
#include "InfectionCardDeck.h"
#include "Map.h"
#include "MapEditor.h"
#include "Menu.h"
#include "Pandemic.h"
#include "Player.h"
#include "PlayerCityCard.h"
#include "Serialization.h"
#include "Util.h"
#include "GameStatistics.h"
#include "OutbreakCounter.h"

//	----    Program entry point    ----  //
void main()
{
	// Title display
	std::cout << titleFont("PANDEMIC") << "\n\n\n";
	mainMenu.solicitInput();

	while (!Board::instance().shouldQuit())
	{
		auto& currentPlayer = Board::instance().nextPlayer();
		std::cout << "\n  --  " << currentPlayer.name() << "'s turn.  --  \n\n";
		while (!turnMenu.solicitInput()); // Intentionally empty body
		Board::instance().distributePlayerCards(cardsPerTurn);
		currentPlayer.displayCards();
		infect();
	}

	waitForExit();
}

//  -----  Function definitions  ----  //

// The player wants to start a new game
void newGame()
{
	std::cout << titleFont("NEW GAME") << "\n\n";

	// Initialize game state
	//game = std::make_unique<Board>();

	// Get map file name and load it
	const auto& fileName = solicitFileName("Load map file to start new game: ");
	std::cout << "\nLoading map \"" << fileName << "\"...\n";
	Board::instance().setMap(readMapFromFile(fileName));
	std::cout << "Map \"" << fileName << "\" loaded!\n\n";

	// Create players
	std::cout << "How many players? ";
	const auto& numPlayers = solicitSize(minPlayers, maxPlayers);
	const auto& map = Board::instance().map();	// alias
	for (auto i = 1; i <= numPlayers; ++i)
	{
		// For each player - get name, set position to starting city, give to game state
		const auto& playerName = solicitPlayerName(i);
		auto player = std::make_unique<Player>();
		player->setName(playerName);
		player->pawn().setPosition(map.startingCity());
		Board::instance().addPlayer(std::move(player));
	}

	// Other initializtion here - cards, etc
	for (const auto& city : Board::instance().map().cities())
	{
		Board::instance().playerDeck().addToDeck(std::make_unique<PlayerCityCard>(*city));
		Board::instance().infectionDeck().addToDeck(std::make_unique<InfectionCard>(*city));
		
	}
	
	auto eventCards = DeckofEvents {}.deckOfEvents();
	while (!eventCards.empty())
	{
		Board::instance().playerDeck().addToDeck(std::move(eventCards.back()));
		eventCards.pop_back();
	}


	//Distribute Role Cards to players
	DeckofRoles roleCardDeck;
	for (auto& player : Board::instance().players())
	{
		player->setRole(roleCardDeck.drawRoleCard());
	}

	for (const auto& player : Board::instance().players())
	{
		std::cout << "Player " << player->name() << " has the role of " << player->role().name() << std::endl;
	}

	Board::instance().playerDeck().shuffleDeck();

	// Distribute cards to players
	for (const auto& player : Board::instance().players())
	{
		for (auto i = 0u; !Board::instance().playerDeck().empty() && i < Board::instance().initialCards(); ++i)
		{
			player->addCard(std::move(Board::instance().playerDeck().drawTopCard()));
		}
	}

	for (const auto& player : Board::instance().players())
	{
		std::cout << "Player " << player->name() << " has\n";
		for (const auto& card : player->cards())
		{
			std::cout << "\t" << card->name() << "\n";
		}
	}
	
	//Place first research station
	map.startingCity().giveResearchStation(Board::instance());

	//Initial distribution of disease cubes during game initialization
	Board::instance().infectionDeck().shuffleDeck();
	std::cout << "Initial infected cities are as follows:" << std::endl;
	for (auto j = 3; j >= 1; --j)
	{
		for (auto i = 0; i < 3; ++i)
		{
			if (Board::instance().infectionDeck().empty())
			{
				break;
			}
			auto temp = Board::instance().infectionDeck().drawTopCard();
			temp->infect(Board::instance(), j);
			Board::instance().infectionDeck().addToDiscard(move(temp));
		}
	}
}
GameStatistics *observer = new GameStatistics(Board::instance());
//Initialize a reference card that any player can view
void displayReferenceCard()
{
	std::cout << "Drive / Ferry: \nMove to a city connected by a white line to the one you are in.\n"
		"Direct Flight: \nDiscard a city card to move to the city named on the card.\n"
		"Charter Flight: \nDiscard the city card that MATCHES the city you are in to move to ANY city.\n"
		"Shuttle Flight: \nMove from a city with a research station to any other city that has a research station.\n"
		"Build a Research Station: \nDiscard the city card that matches the city you are in to place a research station there. \n"
		"Take the research station from the pile next to the bard. If all the 6 research stations \n"
		"have been builtm take a research station from anywhere on the board.\n"
		"Treat Disease: \nRemove 1 disease cube from the city you are in, placing it in the cube suppled next to the board. \n"
		"If this disease color has been cured (see Discover a Cure below), remove all cubes of that color from \n"
		"the city you are in. \n If the LAST CUBE of a CURED DISEASE is removed from the board, this disease is \n"
		"ERADICATED. Flip its cure marker from its VIAL side to its ERADICATED side\n"
		"Share Knowledge: \nYou can do this action in two ways: \n GIVE the city card that matches the city you are in to another \n"
		"player, or \n TAKE a city card that matches the city you are in from another player. \n  The other player \n"
		"must also be in the city with you. Both of you need to agree to do this. if the player who gets the card \n"
		"now has more than 7 cards, that player must immediately discard a card or play an Event card.\n"
		"Discover a Cure: \nAt ANY research station, discard 5 city cards of the same color from your hand to cure the disease of THAT \n"
		"COLOR. Move the disease's cure marker to its Cure indicator. \n If no cubes of this color are on the board, this \n"
		"disease if now ERADICATED. Flip its cure marker from its VIAL side to its ERADICATED side.\n";
}

void loadGame()
{
	std::cout << "Load game...\n";
	const auto fileName = solicitFileName("Enter name of game save file: ");
	//game = readGameFromFile(fileName);
	std::cout << "\n\n" << titleFont("RESUMING GAME") << "\n\n";
}

bool saveGame()
{
	std::cout << "Save game...\nEnter name of game save file : ";
	std::string fileName;
	std::cin >> fileName;
	std::cin.ignore();
	if (fileExists(fileName))
	{
		std::cout << "File exists. Overwrite? (Y/N)" << std::endl;
		char overwrite;
		std::cin >> overwrite;
		if (!(overwrite == 'y' || overwrite == 'Y'))
		{
			return false;
		}
	}
	saveGame(Board::instance(), fileName);
	std::cout << "\n" << titleFont("GAME SAVED") << "\n\n";
	return false;
}

// The player wants to quit
void waitForExit()
{
	std::cout << "\nThanks for playing!\n";
	std::cout << "Press any key to continue...\n";
	std::cin.get();
}

// On a player's turn, allow four actions
bool performAction()
{
	ActionController controller(Board::instance().currentPlayer());
	while (controller.hasActionPoints())
	{
		controller.solicitAction();
	}
	return true;
}

// The player moves their pawn from its current position to another directly connected city.
// An action: Returns true iff the drive/ferry was completed
bool driveOrFerry()
{
	// Aliases
	auto& player = Board::instance().currentPlayer();
	const auto& position = player.pawn().position();
	const auto& connections = position.connections();

	std::cout << "You are currently in " << position.name() << "\n";

	// Check if there are no connections - should not happen in a well-formed map
	if (connections.empty())
	{
		std::cout << "Nowhere you can drive/ferry to.\n";
		return false;
	}

	// List connections
	std::cout << "You can move to\n";
	list(position.connections());

	// Get target from player and move there
	auto& newPosition = solicitConnection(position);
	player.pawn().setPosition(newPosition);

	return true;
}

// The player discards a city card to move to the indicated city.
bool directFlight()
{
	// Aliases
	auto& player = Board::instance().currentPlayer();
	const auto& cards = player.cityCards();

	// You can't discard a card if you have none!
	if (cards.empty())
	{
		std::cout << "You have no city cards.\n";
		return false;
	}

	// List cards, get player target, discard card, and move
	std::cout << "City cards: \n";
	list(cards);
	auto& targetCard = *validateInput(cards, "You have no city card of that name.\n");
	player.pawn().setPosition(targetCard.city());
	player.removeCardByName(targetCard.name());

	return true;
}

// Player discards a city card matching the city they are in to fly to any city.
bool charterFlight()
{
	// Aliases
	auto& player = Board::instance().currentPlayer();
	auto& pawn = player.pawn();

	// Without cards you can't discard
	if (!player.hasPositionCard())
	{
		std::cout << "You don't have any city cards that match your position.\n";
		return false;
	}

	// Get city choice from player, move, and discard card
	std::cout << "Where would you like to fly to? ";
	auto& target = *validateInput(Board::instance().map().nameMap(), "No city of that name exists.\n");
	pawn.setPosition(target);
	player.removeCardByName(player.pawn().position().name());

	return true;
}

// Player moves from a city to a research station to any other city with a research station
bool shuttleFlight()
{
	auto& player = Board::instance().currentPlayer(); // Alias

	// Not applicable if you have no research station in your city
	if (!player.pawn().position().hasResearchStation())
	{
		std::cout << "Your city does not have a research station.\n";
		return false;
	}

	const auto& stations = Board::instance().map().stations(); // Alias

	// If there are no other cities with stations, you can't move anywhere
	if (stations.empty())
	{
		std::cout << "There are no other cities with research stations.\n";
		return false;
	}

	// List stations, get target, and move
	std::cout << "Where do you want to fly?\n";
	list(stations);
	auto& target = *validateInput(stations, "No city of that name has a research station.\n");
	player.pawn().setPosition(target);

	return true;
}

// Player discards a card matching the city they are in to build a research station
bool buildResearchStation()
{
	auto& player = Board::instance().currentPlayer(); // Alias

										  // No cards, no discard
	if (!player.hasPositionCard())
	{
		std::cout << "No city card which matches our current position.\n";
		return false;
	}

	// If there are no remaining research stations, we have to steal from another city
	if (!Board::instance().hasResearchStation())
	{
		auto stations = Board::instance().map().stations(); // Alias
		{
			// Remove your current city from the list of potential targets
			stations.erase(std::find_if(stations.begin(), stations.end(), [&](const auto& c)
			{
				return *c == player.pawn().position();
			}));
		}

		// No targets
		if (stations.empty())
		{
			std::cout << "No research stations left to build.\n";
			return false;
		}

		// Choose city and eradicate station
		auto& target = *validateInput(stations, "No city of that name has a research station.\n");
		target.removeResearchStation(Board::instance());
	}

	// Remove card, place station
	const auto& cards = player.cards();
	const auto& positionName = player.pawn().position().name();
	auto it = std::find_if(cards.begin(), cards.end(), [&](const auto& card)
	{
		return card->name() == positionName;
	});
	player.removeCardByName((*it)->name());
	player.pawn().position().giveResearchStation(Board::instance());

	return true;
}

// The player removes a disease cube of a given colour from a city
bool treatDisease()
{
	auto& position = Board::instance().currentPlayer().pawn().position();
	const auto& diseases = position.diseases();
	if (diseases.empty())
	{
		std::cout << "No disease in this city.\n";
		return false;
	}
	std::cout << "Select a disease:\n";
	for (const auto& disease : diseases)
	{
		std::cout << "\t" << colourName(disease) << "(" << colourAbbreviation(disease) << "): " << position.diseaseCubes(disease) << " cubes\n";
	}

	const auto& colour = validateInput(colourNameMap(), "Not a disease.\n");
	auto& pool = Board::instance().cubePool();
	position.removeDiseaseCubes(colour, 1, pool);

	std::cout << "Disease report\n";
	for (const auto& disease : diseases)
	{
		std::cout << "\t" << colourName(disease) << "(" << colourAbbreviation(disease) << "): " << position.diseaseCubes(disease) << " cubes\n";
	}

	return true;
}

// Give or take a card mathcing the city you are in from another player
bool shareKnowledge()
{
	// Aliases
	auto& currentPlayer = Board::instance().currentPlayer();
	const auto& position = currentPlayer.pawn().position();
	const auto& players = Board::instance().players();

	// Select another player in your city
	std::vector<Player*> others;
	for (const auto& player : players)
	{
		if (player != &currentPlayer && player->pawn().position() == position)
		{
			others.push_back(player);
		}
	}

	if (others.empty())
	{
		std::cout << "No other players in your city.\n";
		return false;
	}

	std::cout << "Who to trade with?\n";
	for (const auto& player : others)
	{
		std::cout << "\t" << player->name() << "\n";
	}
	auto& target = *validateInput(others, "Not a player in this city.\n");

	// Give or take?
	return ActionMenu
	{
		{
			{ "Give Knowledge", [&](){ return giveKnowledge(target); } },
			{ "Take Knowledge", [&](){ return takeKnowledge(target); } },
		}
	}.solicitInput();
}

// Give your city card to another player
bool giveKnowledge(Player& target)
{
	auto& player = Board::instance().currentPlayer();
	const auto& positionCard = player.positionCard();
	if (!positionCard)
	{
		std::cout << "No matching city card to give!\n";
		return false;
	}
	player.giveCard(*positionCard, target);

	return true;
}

// Take the city card from another player
bool takeKnowledge(Player& target)
{
	const auto& positionCard = target.positionCard();
	if (!positionCard)
	{
		std::cout << "No matching city card to take!\n";
		return false;
	}
	target.giveCard(*positionCard, Board::instance().currentPlayer());

	return true;
}

bool cureDisease()
{
	auto& player = Board::instance().currentPlayer();
	if (!player.pawn().position().hasResearchStation())
	{
		std::cout << "No research station in this city.\n";
		return false;
	}
	const auto& cards = Board::instance().currentPlayer().cityCards();
	std::map<Colour, size_t> colourCount;
	for (const auto& colour : colours())
	{
		colourCount[colour] = 0;
	}
	
	std::pair<Colour, bool> cured;
	cured.second = false;

	for (const auto& card : cards)
	{
		const auto& colour = card->colour();
		auto& count = colourCount[colour];
		++count;
		if (count >= 5)
		{
			cured = { colour, true };
			break;
		}
	}

	if (cured.second)
	{
		Board::instance().cureDisease(cured.first);
		return true;
	}

	std::cout << "Not enough cards of a single colour!\n";
	return false;
}

bool actionQuit()
{
	Board::instance().quit();
	return true;
}

City& solicitConnection(const City& source)
{
	std::cout << "Where would you like to move to? ";
	return *validateInput(source.connections(), "No connected city of that name.\n");
}

std::string solicitPlayerName(const size_t number)
{
	std::cout << "Enter the name of player " << number << ": ";
	std::string playerName;
	while (true)
	{
		std::getline(std::cin >> std::ws, playerName);
		if (playerName.empty())
		{
			std::cout << "Player name cannot be empty.\n";
			continue;
		}
		if (Board::instance().nameExists(playerName))
		{
			std::cout << "Player names must be unique.\n";
			continue;
		}
		break;
	}
	return playerName;
}

size_t solicitSize(const size_t min, const size_t max)
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

bool report()
{
	reportMenu.solicitInput();
	return false;
}

void displayCities()
{
	for (const auto& city : Board::instance().map().cities())
	{
		showCity(*city);
	}
}

void directConnectionReport()
{
	std::cout << "In one action, you can move to\n";
	for (const auto& city : Board::instance().currentPlayer().pawn().position().connections())
	{
		showCity(*city);
	}
}

std::string titleFont(const std::string& original)
{
	std::stringstream ss;
	const auto& repeat = [&](const char c, const size_t t)
	{
		for (size_t i = 0; i < t; ++i)
		{
			ss << c;
		}
	};
	const auto& ornament = [&]()
	{
		repeat(' ', 4);
		repeat('-', 8);
		repeat(' ', 4);
	};
	const auto& insertSpaces = [&]()
	{
		for (auto it = original.begin(); it != original.end(); ++it)
		{
			ss << *it;
			if (it == original.end() - 1)
			{
				break;
			}
			ss << ' ';
		}
	};

	ornament();
	insertSpaces();
	ornament();

	return ss.str();
}

void infect()
{
	for (auto i = 0u; !Board::instance().infectionDeck().empty() && i < Board::instance().infectionRate(); ++i)
	{
		auto card = Board::instance().infectionDeck().drawTopCard();
		card->onDraw(Board::instance());
		Board::instance().infectionDeck().addToDiscard(std::move(card));
	}
	Board::instance().notify();
}
