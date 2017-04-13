#pragma once

#include <vector>
#include <memory>

#include "CubePool.h"
#include "Deck.h"
#include "DiseaseTracker.h"
#include "InfectionCard.h"
#include "InfectionCardDeck.h"
#include "Map.h"
#include "Observable.h"
#include "OutbreakCounter.h"
#include "Player.h"
#include "PlayerCard.h"

class TerminationHandler;

// Represents the state of the game
class Board
	: public Observable
{
public:
	// Signleton instance
	static Board& instance();

	// Player management
	std::vector<Player*> players();
	void addPlayer(std::unique_ptr<Player> player);
	Player& nextPlayer();
	Player& currentPlayer();
	Player& setCurrentPlayer(const size_t idx);
	bool nameExists(const std::string& name) const;

	// Map management
	Map& map() const;
	void setMap(std::unique_ptr<Map> map);
	
	// Quitting
	virtual bool shouldQuit() const;
	void quit();

	// Research stations
	unsigned researchStations() const;
	void removeResearchStation();
	void returnResearchStation();
	bool hasResearchStation() const;

	// Diseases
	void cureDisease(const Colour& colour);
	bool isCured(const Colour& colour) const;
	bool isEradicated(const Colour& colour) const;
	size_t diseaseCount(const Colour& colour) const;
	CubePool& cubePool();

	// Infection rate counter
	void advanceInfectionCounter();
	unsigned infectionRate() const;
	unsigned infectionCounter() const;
	size_t infectedCityCounter() const;
	
	// Outbreak counter
	size_t outbreaks() const;
	void advanceOutbreakCounter();

	// Cards
	Deck<PlayerCard>& playerDeck();
	InfectionCardDeck& infectionDeck();
	size_t initialCards() const;
	void distributePlayerCards(const size_t count);

private:
	// Private ctor/dtor for singleton
	Board();
	~Board();

	std::unique_ptr<Map> _map;
	std::vector<std::unique_ptr<Player>> _players;
	size_t _currentPlayerIdx = std::numeric_limits<size_t>::max();
	CubePool _cubePool;
	DiseaseTracker _diseaseTracker;
	unsigned _infectionCounter = 1;
	unsigned _researchStations = 6;
	Deck<PlayerCard> _playerDeck;
	InfectionCardDeck _infectionDeck;
	OutbreakCounter _outbreakCounter;
	std::unique_ptr<TerminationHandler> _terminationHandler;
};
