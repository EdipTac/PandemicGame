#include <algorithm>
#include "GameStatistics.h"
#include "Board.h"
#include <iostream>

GameStatistics::GameStatistics() {};
GameStatistics::GameStatistics(Board &state) {
	 _state = &state;
	 _state->subscribe(*this);
}
GameStatistics::~GameStatistics() {
	_state->unsubscribe(*this);
}
void GameStatistics::update(){
	display();
}
void GameStatistics::display() {
	std::cout << "Game statistic: \n" << "Number of cities infected by players: " << _state->infectedCityCounter() << "\n" << 
		"Number of cards on each player's hand: " << std::endl;
	for (const auto& player : Board::instance().players())
	{
		unsigned countCity = 0; unsigned countEvent = 0;
		for (const auto& card : player->cards())
		{
			if (card->isCityCard())
				countCity++;
			else
				countEvent++;
		}
		std::cout << "Player " << player->name() << " has " << countCity << " city card(s) " << countEvent << " event card(s)" << std::endl;
	
	}
	std::cout << "The remaining diseases cubes on map: " << std::endl;
	for (const auto& color : colours()) {
		std::cout << "Disease " << colourName(color) << ": " << Board::instance().diseaseCount(color) << " cube(s) " << std::endl;
	}
	
	unsigned countCity = 0; unsigned countEvent = 0;
	for (const auto& card : Board::instance().playerDeck().drawPile())
	{
			if (card->isCityCard())
				countCity++;
			else
				countEvent++;
		}
	std::cout << "The remaining resource: \n" << countCity << " city card(s) and " << countEvent << " event card(s)\n" <<
		Board::instance().researchStations() << " Research stations " << std::endl;




}



