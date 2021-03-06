//			  Pandemic  -   Build 2
//			-------------------------
//
//
//					 Authors
//		================================
//		  Michael Deom	-	29549641
//		  Jonny Linton	-	
//		  Edip Tac		-	26783287
//		  Kechun Ye		-	25654688
//
//
//	  Build 2 submitted 18/04/2017.
//	  An implementation of the board game "Pandemic" by Z-Man Games in C++.

#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

#include "ActionController.h"
#include "Board.h"
#include "BoardBuilder.h"
#include "Card.h"
#include "City.h"
#include "DeckOfRoles.h"
#include "DeckOfEvents.h"
#include "EventCard.h"
#include "EpidemicCard.h"
#include "GameStatistics.h"
#include "InfectedCityPercentage.h"
#include "InfectionCard.h"
#include "Map.h"
#include "MapEditor.h"
#include "Menu.h"
#include "Pandemic.h"
#include "Player.h"
#include "PlayerCityCard.h"
#include "RemainingInfectionCard.h"
#include "SaveBuilder.h"
#include "TreatmentPriority.h"
#include "Util.h"
#include "Quit.h"

//	----    Program entry point    ----  //
void main()
{
	// Title display
	std::cout << titleFont("pandemic") << "\n\n\n";

	// Main game loop
	try
	{
		mainMenu.solicitInput();
		
		auto observer = std::make_unique<GameStatistics>(Board::instance());
		auto decorator = std::make_unique<InfectedCityPercentage>(observer.get());		// city infection rate decorator initilization
		auto infectDecro = std::make_unique<RemainingInfectionCard>(decorator.get());	// remaining infection card decorator initilization
		auto infectStatus = std::make_unique<TreatmentPriority>(infectDecro.get());		// treatment priority decorator initilization

		while (true)
		{
			auto& currentPlayer = Board::instance().currentPlayer();
			std::cout << "\n  --  " << currentPlayer.name() << "'s turn.  --  \n\n";
			while (!turnMenu.solicitInput()); // Intentionally empty body
			Board::instance().distributePlayerCards(cardsPerTurn);
			if (!currentPlayer.isOneQuietNight())
			{
				infect();
			}
			else
			{
				currentPlayer.setOneQuietNight(false);
			}
			Board::instance().nextPlayer();
		}
	}
	catch (const Quit& q)
	{
		std::cout << "\n" << q.what() << "\n";
	}

	waitForExit();
}

//  -----  Function definitions  ----  //

// The player wants to start a new game
void newGame()
{
	std::cout << titleFont("new game") << "\n\n";

	// Get map file name and load it
	const auto& fileName = solicitFileName("Load map file to start new game: ");
	std::cout << "\nLoading map \"" << fileName << "\"...\n";
	Board::instance().setMap(readMapFromFile(fileName));
	std::cout << "Map \"" << fileName << "\" loaded!\n\n";
	Board::instance().map().setName(fileName); // set the name of the Map to the fileName

	// Create players
	std::cout << "How many players? ";
	const auto& numPlayers = solicitSize(minPlayers, maxPlayers, true);
	
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

	std::cout << "\nSelect difficulty:\n\n";
	std::cout << "  Level           Epidemic Cards\n";
	std::cout << " ================================\n";
	std::cout << "  Introductory    4\n";
	std::cout << "  Standard        5\n";
	std::cout << "  Heroic          6\n\n";

	const auto& numEpidemicCards = solicitEpidemicCardNumber(minEpidemicCards, maxEpidemicCards);

	// Other initializtion here - cards, etc
	for (const auto& city : Board::instance().map().cities())
	{
		Board::instance().playerDeck().addToDeck(std::make_unique<PlayerCityCard>(*city));
		Board::instance().infectionDeck().addToDeck(std::make_unique<InfectionCard>(*city));
	}
	
	auto eventCards = event::cards();
	while (!eventCards.empty())
	{
		Board::instance().playerDeck().addToDeck(std::move(eventCards.back()));
		eventCards.pop_back();
	}

	// Distribute Role Cards to players
	auto roles = role::cards();
	for (auto& player : Board::instance().players())
	{
		player->setRole(std::move(roles.back()));
		roles.pop_back();
	}

	for (const auto& player : Board::instance().players())
	{
		std::cout << "Player " << player->name() << " has the role of " << player->role().name() << std::endl;
	}

	Board::instance().playerDeck().shuffleDeck();

	// Distribute cards to players
	size_t numPlayerDistributed = 0;
	for (const auto& player : Board::instance().players())
	{
		for (auto i = 0u; !Board::instance().playerDeck().empty() && i < Board::instance().initialCards(); ++i)
		{
			player->addCard(std::move(Board::instance().playerDeck().drawTopCard()));
			numPlayerDistributed++;
		}
	}

	// Shuffle epidemic cards into play card deck
	Board::instance().playerDeck().addEpidemicCards(numEpidemicCards);
	for (const auto& player : Board::instance().players())
	{
		std::cout << "\n" << player->name() << ": ";
		player->role().print();
		player->displayCards();
	}
	
	// Place first research station
	map.startingCity().giveResearchStation();

	// Initial distribution of disease cubes during game initialization
	Board::instance().infectionDeck().shuffleDeck();
	std::cout << "\nInitial infected cities are as follows:" << std::endl;
	for (auto j = 3; j >= 1; --j)
	{
		for (auto i = 0; i < 3; ++i)
		{
			if (Board::instance().infectionDeck().empty())
			{
				break;
			}
			auto temp = Board::instance().infectionDeck().drawTopCard();
			temp->infect(j);
			Board::instance().infectionDeck().addToDiscard(move(temp));
		}
	}
}

// Initialize a reference card that any player can view
void displayReferenceCard()
{
	std::cout << "\n"
		" - Drive / Ferry: Move to a city connected by a white line to the one you are in.                                     \n"
		" - Direct Flight: Discard a city card to move to the city named on the card.                                          \n"
		" - Charter Flight: Discard the city card that MATCHES the city you are in to move to ANY city.                        \n"
		" - Shuttle Flight: Move from a city with a research station to any other city that has a research station.            \n"
		" - Build a Research Station:                                                                                          \n"
		"       Discard the city card that matches the city you are in to place a research station there.                      \n"
		"       Take the research station from the pile next to the bard. If all the 6 research stations                       \n"
		"       have been built take a research station from anywhere on the board.                                            \n"
		" - Treat Disease: Remove 1 disease cube from the city you are in, placing it in the cube suppled next to the board.   \n"
		"       If this disease color has been cured (see Discover a Cure below), remove all cubes of that color from          \n"
		"       the city you are in. If the LAST CUBE of a CURED DISEASE is removed from the board, this disease is            \n"
		"       ERADICATED. Flip its cure marker from its VIAL side to its ERADICATED side.                                    \n"
		" - Share Knowledge: You can do this action in two ways:                                                               \n"
		"        + GIVE the city card that matches the city you are in to another player, or                                   \n"
		"        + TAKE a city card that matches the city you are in from another player.                                      \n"
		"       The other player must also be in the city with you. Both of you need to agree to do this. If the player        \n"
		"       who gets the card now has more than 7 cards, that player must immediately discard a card or play an Event card.\n"
		" - Discover a Cure: At ANY research station, discard 5 city cards of the same color from your hand to cure the disease\n"
		"       of THAT COLOR. Move the disease's cure marker to its Cure indicator. If no cubes of this color are on the      \n"
		"       board, this disease is now ERADICATED. Flip its cure marker from its VIAL side to its ERADICATED side.         \n\n";
}

void loadGame()
{
	std::cout << "Load game...\n";
	auto fileName = solicitFileName("Enter name of game save file: ");
	std::cout << "\nLoading game \"" << fileName << "\"...\n";
	BoardBuilder().loadBoard(fileName).loadPlayers().loadCities().loadInfectionCards().loadPlayerCards();
	std::cout << "Game \"" << fileName << "\" loaded!\n\n";
	std::cout << "\n\n" << titleFont("resuming game") << "\n\n";
}

bool saveGame()
{
	std::cout << "Save game...\n";
	std::cout << "Enter name of game save file : ";

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

	SaveBuilder()
		.saveMap()
		.savePlayers()
		.savePlayerCards()
		.saveInfectionCards()
		.saveCities()
		.persist(fileName);

	std::cout << "\n" << titleFont("game saved") << "\n\n";
	
	return false;
}

// The player wants to quit
void waitForExit()
{
	std::cout << "\nThanks for playing!\n";
	std::cout << "Press any key to continue...\n";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

// On a player's turn, allow four actions
bool performAction()
{
	ActionController controller(Board::instance().currentPlayer());
	while (controller.hasActionPoints())
	{
		std::cout << Board::instance().currentPlayer().name() << " is at " << Board::instance().currentPlayer().pawn().position().name() << "\n" << "Has research station: " << Board::instance().currentPlayer().pawn().position().hasResearchStation() << "\n\n";
		const auto& diseases = Board::instance().currentPlayer().pawn().position().diseases();
		for (const auto& disease : diseases)
		{
			std::cout << "\t" << colourName(disease) << "(" << colourAbbreviation(disease) << "): " << Board::instance().currentPlayer().pawn().position().diseaseCubes(disease) << " cubes\n";
		}
		
		controller.solicitAction();
	}
	return true;
}

// Do nothing
bool skipAction()
{
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

	// For alignment
	size_t maxSize = 0;
	for (const auto& cardOwner : cardOwners)
	{
		const auto& size = cardOwner.first->name().size();
		maxSize = std::max(size, maxSize);
	}
	const auto width = maxSize + 1;
	
	// Construct menu
	Menu<EventCard*> menu;
	menu.setMessage("\t    " + rightPad("<Card>", width) + " [<Owner>]");
	for (const auto& cardOwner : cardOwners)
	{
		const auto& card = cardOwner.first;
		const auto& owner = cardOwner.second;
		const auto& label = rightPad(card->name(), width) + " [" + owner->name() + "]";
		const auto& function = [&]()
		{
			return card;
		};
		menu.addOption({ label, function });
	}
	menu.addOption({ "Back", [](){ return nullptr; } });

	// Display and solicit
	auto cardToPlay = menu.solicitInput();

	if (!cardToPlay)
	{
		// Back
		return false;
	}

	// Perform event action, and discard if completed
	cardToPlay->ability().solicitData();
	if (cardToPlay->ability().isValid())
	{
		cardToPlay->ability().perform();
		cardOwners[cardToPlay]->discard(*cardToPlay, Board::instance().playerDeck());
	}

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

size_t solicitEpidemicCardNumber(const size_t min, const size_t max)
{
	size_t size;
	while (true)
	{
		std::cout << "Enter the number of epidemic cards from " << min << " to " << max << ", inclusive: ";
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
	const auto& cities = Board::instance().map().cities();
	std::cout << "\n";
	Menu<City*> cityMenu;
	cityMenu.setMessage("Select a city: ");
	for (const auto& city : cities)
	{
		cityMenu.addOption({ city->name(), [&]() { return city; } });
	}
	cityMenu.addOption({ "Back", []() { return nullptr; } });
	const auto city = cityMenu.solicitInput();
	std::cout << (city ? city->string() : "");
}

void displayCurrentPosition() 
{
	std::cout << "You are in " << Board::instance().currentPlayer().pawn().position().string();
}

void displayCardsInHand() 
{
	// For aligning card labels
	const auto& cards = Board::instance().currentPlayer().cards();
	size_t maxLength = 0;
	for (const auto& card : cards)
	{
		maxLength = std::max(maxLength, card->rawString().size());
	}

	// Construct menu
	Menu<void> menu;
	menu.setMessage("Select a card to display description :");
	for (const auto& card : cards)
	{
		const auto& label = card->string(maxLength + 2 - card->rawString().size());
		const auto& displayFunction = [&]()
		{
			std::cout << "  " << card->description() << "\n\n";
		};
		menu.addOption({ label, displayFunction });
	}
	menu.addOption({ "Back", [](){} });

	// Display and prompt for description
	std::cout << "\nHand:\n";
	menu.solicitInput();
}

void displayRole()
{
	const auto& role = Board::instance().currentPlayer().role();
	std::cout << "Role: " << role.name() << "\n";
	std::cout << "Description: " << role.description() << "\n\n";
}

void directConnectionReport()
{
	std::cout << "In one action, you can move to\n";
	for (const auto& city : Board::instance().currentPlayer().pawn().position().connections())
	{
		std::cout << "  " << city->name() << "\n";
	}
	std::cout << "\n";
}

void infect()
{
	for (auto i = 0u; !Board::instance().infectionDeck().empty() && i < Board::instance().infectionRate(); ++i)
	{
		auto card = Board::instance().infectionDeck().drawTopCard();
		card->onDraw();
		Board::instance().infectionDeck().addToDiscard(std::move(card));
	}	
	Board::instance().notify();	
}
