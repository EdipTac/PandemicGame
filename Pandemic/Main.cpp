//  Pandemic - Assignment 2
//
//					Authors
//		============================
//		Edip Tac		-	26783287

#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "Card.h"
#include "City.h"
#include "DeckofEvents.h"
#include "DeckofRoles.h"
#include "EventCard.h"
#include "GameState.h"
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
#include "ResearchStationsAndDiseases.h"
#include "ResearchStationsAndDiseasesView.h"

void newGame()
{
	std::cout << titleFont("NEW GAME") << "\n\n";

	ResearchStationsAndDiseases *nonview = new ResearchStationsAndDiseases;

	//ResearchStationsAndDiseasesView *view = new ResearchStationsAndDiseasesView(nonview);

	std::vector <City*> cities;






	