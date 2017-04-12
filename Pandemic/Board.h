#pragma once

#include <vector>
#include <memory>

#include "CubePool.h"
#include "Deck.h"
#include "DiseaseTracker.h"
#include "InfectionCard.h"
#include "Map.h"
#include "Player.h"
#include "PlayerCard.h"
#include "OutbreakCounter.h"
#include "Observable.h"

class TerminationHandler;

// Represents the state of the game
class Board
	: public Observable
{
public:
	static Board& instance();
	Board();
	~Board();
	std::vector<Player*> players();
	Map& map() const;
	void addPlayer(std::unique_ptr<Player> player);
	void setMap(std::unique_ptr<Map> map);
	virtual bool shouldQuit() const;

	void quit();

	Player& nextPlayer();
	Player& currentPlayer();
	Player& setCurrentPlayer(const size_t idx);
	bool nameExists(const std::string& name) const;

	unsigned researchStations() const;
	void removeResearchStation();
	void returnResearchStation();
	bool hasResearchStation() const;
	void cureDisease(const Colour& colour);
	bool isCured(const Colour& colour) const;
	bool isEradicated(const Colour& colour) const;
	size_t diseaseCount(const Colour& colour) const;

	void advanceInfectionCounter();
	unsigned infectionRate() const;
	unsigned infectionCounter() const;
	size_t infectedCityCounter() const;
	CubePool& cubePool();
	
	Deck<PlayerCard>& playerDeck();
	Deck<InfectionCard>& infectionDeck();
	size_t initialCards() const;
	void distributePlayerCards(const size_t count);

	size_t outbreaks() const;
	void advanceOutbreakCounter();

private:
	std::unique_ptr<Map> _map;
	std::vector<std::unique_ptr<Player>> _players;
	size_t _currentPlayerIdx = std::numeric_limits<size_t>::max();
	CubePool _cubePool;
	DiseaseTracker _diseaseTracker;
	unsigned _infectionCounter = 1;
	bool _shouldQuit = false;
	unsigned _researchStations = 6;
	Deck<PlayerCard> _playerDeck;
	Deck<InfectionCard> _infectionDeck;
	OutbreakCounter _outbreakCounter;
	std::unique_ptr<TerminationHandler> _terminationHandler;
};
