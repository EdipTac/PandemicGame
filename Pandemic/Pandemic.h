#pragma once

#include "Menu.h"

//  ----  Forward declarations  ----  //
void directConnectionReport();
void displayCities();
void displayReferenceCard();
void displayCurrentPosition();
void displayCardsInHand();
void displayRole();
void infect();
void loadGame();
void newGame();
void waitForExit();

bool actionQuit();
bool performAction();
bool skipAction();
bool playEventCard();
bool report();
bool saveGame();

size_t solicitSize(const size_t min, const size_t max);

std::string solicitFileName(const std::string& msg);
std::string solicitPlayerName(const size_t number);
std::string titleFont(const std::string& original);

City& solicitConnection(const City& source);

template <typename T> void list(const T& collection);
template <typename T> T validateInput(const std::map<std::string, T>& validInputs, const std::string& errMsg);
template <typename T> T validateInput(const std::vector<T>& valid, const std::string& errMsg);

const auto& saveGameAction = static_cast<bool(*)()>(saveGame);

//  ----  Game pointer - global data  ----  //
//std::unique_ptr<Board> game;

//  ----  Constants  -----  //
constexpr size_t minPlayers = 2;
constexpr size_t maxPlayers = 4;
constexpr size_t actionsPerTurn = 4;
constexpr size_t cardsPerTurn = 2;

//  ----  Menus  ----  //
const GeneralMenu mainMenu
{
	{
		{ "New Game",	newGame },
		{ "Load Game",	loadGame },
		{ "Map Editor",	mapEditor },
		{ "Exit",		[](){actionQuit();} }
	}
};

const ActionMenu turnMenu
{
	{
		{ "Report",			 report			},
		{ "Perform Action",  performAction	},
		{ "Play Event Card", playEventCard	},
		{ "Skip Turn",		 skipAction     },
		{ "Save Game",		 saveGameAction	},
		{ "Quit Game",		 actionQuit		}
	}
};

const GeneralMenu reportMenu
{
	{
		{ "Display Cities",				displayCities },
		{ "Display Reference Card",	displayReferenceCard },
		{ "Direct Connection Report",	directConnectionReport },
		{ "Display Current Position",	displayCurrentPosition },
		{ "Display Role",	displayRole },
		{ "Display Cards in Hand",	displayCardsInHand }
	}
};
