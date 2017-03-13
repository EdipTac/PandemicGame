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
#include "EventCard.h"
#include "DeckofEvents.h"
#include "GameState.h"
#include "InfectionCard.h"
#include "InfectionCardDeck.h"
#include "Map.h"
#include "MapEditor.h"
#include "Menu.h"
#include "Player.h"
#include "PlayerCityCard.h"
#include "Serialization.h"
#include "Util.h"


//  ----  Forward declarations  ----  //
void newGame();
void loadGame();
bool saveGame();
void waitForExit();
bool performAction();
void quit();
bool driveOrFerry();
bool directFlight();
bool charterFlight();
bool shuttleFlight();
bool buildResearchStation();
bool treatDisease();
bool shareKnowledge();
bool giveKnowledge(Player& target);
bool takeKnowledge(Player& target);
bool cureDisease();
bool actionQuit();
bool report();
void displayCities();
void directConnectionReport();
void infect();
std::string solicitFileName(const std::string& msg);
City& solicitConnection(const City& source);
std::string solicitPlayerName(const size_t number);
size_t solicitSize(const size_t min, const size_t max);
template <typename T> T validateInput(const std::map<std::string, T>& validInputs, const std::string& errMsg);
template <typename T> T validateInput(const std::vector<T>& valid, const std::string& errMsg);
template <typename T> void list(const T& collection);
std::string titleFont(const std::string& original);

// Game pointer
std::unique_ptr<GameState> game;

//  ----  Constants  -----  //
constexpr size_t minPlayers		= 1;
constexpr size_t maxPlayers		= 4;
constexpr size_t actionsPerTurn	= 4;
constexpr size_t cardsPerTurn	= 2;

//  ----  Menus  ----  //
const GeneralMenu mainMenu
{
	{
		{ "New Game",	newGame		},
		{ "Load Game",	loadGame	},
		{ "Map Editor",	mapEditor	},
		{ "Exit",		quit		}
	}
};

// Return true iff the action 
const ActionMenu turnMenu
{
	{
		{ "Report",			report								},
		{ "Perform Action",	performAction						},
		{ "Save Game",		static_cast<bool(*)()>(saveGame)	},
		{ "Quit Game",		actionQuit							}
	}
};

const GeneralMenu reportMenu
{
	{
		{ "Display Cities",				displayCities			},
		//{ "City Report",				cityReport				},
		{ "Direct Connection Report",	directConnectionReport	}
	}
};

const ActionMenu actionMenu
{
	{
		{ "Drive/Ferry",				driveOrFerry			},
		{ "Direct Flight",				directFlight			},
		{ "Charter Flight",				charterFlight			},
		{ "Shuttle Flight",				shuttleFlight			},
		{ "Build a Research Station",	buildResearchStation	},
		{ "Treat Disease",				treatDisease			},
		{ "Share Knowledge",			shareKnowledge			},
		{ "Cure Disease",				cureDisease				},
		{ "Quit Game",					actionQuit				}
	}
};

//	----    Program entry point    ----  //
//#define TEST
#ifdef TEST
void main()
{
	game = readGameFromFile("save.json");
	game->currentPlayer().setRole(std::make_unique<RoleCard>("Ayyy", "Lmao"));
	saveGame(*game);
}
#else
void main()
{
	// Title display
	std::cout << titleFont("PANDEMIC") << "\n\n\n";
	mainMenu.solicitInput();

	while (!game->shouldQuit())
	{
		auto& currentPlayer = game->nextPlayer();
		std::cout << currentPlayer.name() << "'s turn.\n";
		while (!turnMenu.solicitInput()); // Intentionally empty body
		game->distributePlayerCards(cardsPerTurn);
		infect();
	}

	waitForExit();
}
#endif

// The player wants to start a new game
void newGame()
{
	std::cout << titleFont("NEW GAME") << "\n\n";

	// Initialize game state
	game = std::make_unique<GameState>();

	// Get map file name and load it
	const auto& fileName = solicitFileName("Load map file to start new game: ");
	std::cout << "\nLoading map \"" << fileName << "\"...\n";
	game->setMap(readMapFromFile(fileName));
	std::cout << "Map \"" << fileName << "\" loaded!\n\n";

	// Create players
	std::cout << "How many players? ";
	const auto& numPlayers = solicitSize(minPlayers, maxPlayers);
	const auto& map = game->map();	// alias
	for (auto i = 1; i <= numPlayers; ++i)
	{
		// For each player - get name, set position to starting city, give to game state
		const auto& playerName = solicitPlayerName(i);
		auto player = std::make_unique<Player>();
		player->setName(playerName);
		player->pawn().setPosition(map.startingCity());
		game->addPlayer(std::move(player));
	}

	// Other initializtion here - cards, etc
	for (const auto& city : game->map().cities())
	{
		game->playerDeck().addToDeck(std::make_unique<PlayerCityCard>(*city));
		game->infectionDeck().addToDeck(std::make_unique<InfectionCard>(*city));
	}
	
	auto eventCards = DeckofEvents {}.deckOfEvents();
	while (!eventCards.empty())
	{
		game->playerDeck().addToDeck(std::move(eventCards.back()));
		eventCards.pop_back();
	}

	game->playerDeck().shuffleDeck();

	// Distribute cards to players
	for (const auto& player : game->players())
	{
		for (auto i = 0u; !game->playerDeck().empty() && i < game->initialCards(); ++i)
		{
			player->addCard(std::move(game->playerDeck().drawTopCard()));
		}
	}

	for (const auto& player : game->players())
	{
		std::cout << "Player " << player->name() << " has\n";
		for (const auto& card : player->cards())
		{
			std::cout << "\t" << card->name() << "\n";
		}
	}

	//Place first research station
	map.startingCity().giveResearchStation(*game);

}

void loadGame()
{
	std::cout << "Load game...\n";
	const auto fileName = solicitFileName("Enter name of game save file: ");
	game = readGameFromFile(fileName);
	std::cout << "\n" << titleFont("RESUMING GAME") << "\n\n";
}

bool saveGame()
{
	std::cout << "Save game...\nEnter name of game save file : ";
	std::string fileName;
	std::cin >> fileName;
	std::cin.ignore();
	saveGame(*game, fileName);
	std::cout << "\n" << titleFont("GAME SAVED") << "\n\n";
	return false;
}

// The player wants to quit
void waitForExit()
{
	std::cout << "Press any key to continue...\n";
	std::cin.get();
}

// On a player's turn, allow four actions
bool performAction()
{
	auto actions = actionsPerTurn;	// Counter
	while (!game->shouldQuit() && actions > 0)	// To check game loss/win state between actions
	{
		std::cout << "You have " << actions << " actions remaining.\n";
		// Sometimes actions cannot be completed - these do not count towards your limit of four!
		const auto& actionCompleted = actionMenu.solicitInput();
		if (actionCompleted)
		{
			--actions;
		}
	}
	return true;
}

// The player moves their pawn from its current position to another directly connected city.
// An action: Returns true iff the drive/ferry was completed
bool driveOrFerry()
{
	// Aliases
	auto& player = game->currentPlayer();
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
	auto& player = game->currentPlayer();
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
	auto& player = game->currentPlayer();
	auto& pawn = player.pawn();

	// Without cards you can't discard
	if (!player.hasPositionCard())
	{
		std::cout << "You don't have any city cards that match your position.\n";
		return false;
	}

	// Get city choice from player, move, and discard card
	std::cout << "Where would you like to fly to? ";
	auto& target = *validateInput(game->map().nameMap(), "No city of that name exists.\n");
	pawn.setPosition(target);
	player.removeCardByName(player.pawn().position().name());

	return true;
}

// Player moves from a city to a research station to any other city with a research station
bool shuttleFlight()
{
	auto& player = game->currentPlayer(); // Alias

	// Not applicable if you have no research station in your city
	if (!player.pawn().position().hasResearchStation())
	{
		std::cout << "Your city does not have a research station.\n";
		return false;
	}

	const auto& stations = game->map().stations(); // Alias

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
	auto& player = game->currentPlayer(); // Alias

										  // No cards, no discard
	if (!player.hasPositionCard())
	{
		std::cout << "No city card which matches our current position.\n";
		return false;
	}

	// If there are no remaining research stations, we have to steal from another city
	if (!game->hasResearchStation())
	{
		auto stations = game->map().stations(); // Alias
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
		target.removeResearchStation(*game);
	}

	// Remove card, place station
	const auto& cards = player.cards();
	const auto& positionName = player.pawn().position().name();
	auto it = std::find_if(cards.begin(), cards.end(), [&](const auto& card)
	{
		return card->name() == positionName;
	});
	player.removeCardByName((*it)->name());
	player.pawn().position().giveResearchStation(*game);

	return true;
}

// The player removes a disease cube of a given colour from a city
bool treatDisease()
{
	auto& position = game->currentPlayer().pawn().position();
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
	auto& pool = game->cubePool();
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
	auto& currentPlayer = game->currentPlayer();
	const auto& position = currentPlayer.pawn().position();
	const auto& players = game->players();

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
	auto& player = game->currentPlayer();
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
	target.giveCard(*positionCard, game->currentPlayer());

	return true;
}

bool cureDisease()
{
	auto& player = game->currentPlayer();
	if (!player.pawn().position().hasResearchStation())
	{
		std::cout << "No research station in this city.\n";
		return false;
	}
	const auto& cards = game->currentPlayer().cityCards();
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
		game->cureDisease(cured.first);
		return true;
	}

	std::cout << "Not enough cards of a single colour!\n";
	return false;
}

void quit()
{
	game = quitState();
}

bool actionQuit()
{
	quit();
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
		if (!playerName.empty())
		{
			break;
		}
		std::cout << "Player name cannot be empty.\n";
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
	for (const auto& city : game->map().cities())
	{
		showCity(*city);
	}
}

void directConnectionReport()
{
	std::cout << "In one action, you can move to\n";
	for (const auto& city : game->currentPlayer().pawn().position().connections())
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
	for (auto i = 0u; i < game->infectionRate(); ++i)
	{
		auto card = game->infectionDeck().drawTopCard();
		card->onDraw(*game);
		game->infectionDeck().addToDiscard(std::move(card));
	}
}
