//  Pandemic - Build 1
//
//					Authors
//		============================
//		Michael Deom	-	29549641
//		Jonny Linton	-	
//		Edip Tac		-	26783287
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
#include <map>
#include <numeric>

#include "ActionController.h"
#include "Card.h"
#include "City.h"
#include "DeckofEvents.h"
#include "DeckOfRoles.h"
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
#include "BoardBuilder.h"
#include "Util.h"
#include "GameStatistics.h"
#include "OutbreakCounter.h"
#include "SaveBuilder.h"

//	----    Program entry point    ----  //
void main()
{
	// Title display
	std::cout << titleFont("PANDEMIC") << "\n\n\n";
	mainMenu.solicitInput();
	auto observer = std::make_unique<GameStatistics>(Board::instance());

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

	// Get map file name and load it
	const auto& fileName = solicitFileName("Load map file to start new game: ");
	std::cout << "\nLoading map \"" << fileName << "\"...\n";
	Board::instance().setMap(readMapFromFile(fileName));
	std::cout << "Map \"" << fileName << "\" loaded!\n\n";
	Board::instance().map().setName(fileName); // set the name of the Map to the fileName

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
	DeckOfRoles roleCardDeck;
	roleCardDeck.shuffleDeck();
	for (auto& player : Board::instance().players())
	{
		player->setRole(roleCardDeck.drawTopCard());
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
	auto fileName = solicitFileName("Enter name of game save file: ");
	BoardBuilder().loadBoard(fileName).loadPlayers().loadCities().loadInfectionCards().loadPlayerCards();
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
	SaveBuilder().saveMap().savePlayers().savePlayerCards().saveInfectionCards().saveCities().persist(fileName);
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

bool playEventCard()
{
	// To record cards and owners
	std::map<EventCard*, Player*> cardOwners;

	// Load event cards and owners
	for (const auto& player : Board::instance().players())
	{
		for (const auto& card : player->eventCards())
		{
			cardOwners[card] = player;
		}
	}

	// If there are no cards, do nothing
	if (cardOwners.empty())
	{
		std::cout << "No event cards to play.\n";
		return false;
	}

	// Display
	std::cout << "Which card to play?\n";
	size_t maxSize = 0;
	for (const auto& cardOwner : cardOwners)
	{
		const auto& size = cardOwner.first->name().size();
		maxSize = std::max(size, maxSize);
	}
	const auto width = maxSize + 1;
	std::cout << "\t" << rightPad("<Card>", width) << "[<Owner>]\n";
	for (const auto& cardOwner : cardOwners)
	{
		const auto& card = cardOwner.first;
		const auto& owner = cardOwner.second;
		std::cout << "\t" << rightPad(card->name(), width) << " [" << owner->name() << "]\n";
	}

	// Solicit input
	EventCard* cardToPlay = nullptr;
	std::string input;
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(cardOwners.begin(), cardOwners.end(), [&](const auto& c)
		{
			return input == c.first->name();
		});
		if (it != cardOwners.end())
		{
			cardToPlay = it->first;
			break;
		}
		std::cout << "No card of that name.\n";
	}

	// Play and discard card
	//cardToPlay->action() TODO
	cardOwners[cardToPlay]->discard(*cardToPlay, Board::instance().playerDeck());

	// Doesn't cost an action
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
		auto& currentPlayer = Board::instance().nextPlayer();
		if (currentPlayer.isOneQuietNight()) { break; } //added this for the one quiet night event card, should modify it so that once the event is complete, the status of isonequietnight reverts back to false.
		auto card = Board::instance().infectionDeck().drawTopCard();
		card->onDraw(Board::instance());
		Board::instance().infectionDeck().addToDiscard(std::move(card));
	}
	Board::instance().notify();
}
