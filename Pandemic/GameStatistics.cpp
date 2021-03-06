#include <algorithm>
#include <iostream>

#include "Board.h"
#include "GameStatistics.h"

GameStatistics::GameStatistics() {};

GameStatistics::GameStatistics(Board &state) {
	 _state = &state;
	 _state->subscribe(*this);
}

GameStatistics::~GameStatistics() {
	if (_state)
	{
		_state->unsubscribe(*this);
	}
}

void GameStatistics::update(){
	display();
}

void GameStatistics::display() {
	std::cout << "\nGame statistic: \n\n" << "Number of cities infected by players: " << _state->infectedCityCounter() << "\n\n" << 
		"Number of cards on each player's hand: " << std::endl;
	for (const auto& player : Board::instance().players())
	{
		unsigned countCity = 0, countEvent = 0;
		for (const auto& card : player->cards())
		{
			if (card->type() == PlayerCardType::CityCard)
			{
				countCity++;
			}
			else
			{
				countEvent++;
			}
		}
		std::cout << "Player " << player->name() << " has " << countCity << " city card(s) " << countEvent << " event card(s)" << std::endl;
	
	}
	
	unsigned countCity = 0, countEvent = 0;
	for (const auto& card : Board::instance().playerDeck().drawPile())
	{
		if (card->type() == PlayerCardType::CityCard)
		{
			countCity++;
		}
		else
		{
			countEvent++;
		}
	}
	std::cout << "\nThe remaining resource: \n" << countCity << " city card(s) and " << countEvent << " event card(s)\n" <<
		Board::instance().researchStations() << " Research stations\n " << std::endl;
	std::cout << "Outbreak mark: " << Board::instance().outbreaks() << std::endl;
	std::cout << "Infection rate: " << Board::instance().infectionCounter() << "\n\n";
}
