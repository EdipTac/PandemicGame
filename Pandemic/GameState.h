#pragma once

#include <vector>
#include <memory>

#include "CubePool.h"
#include "Deck.h"
#include "InfectionCard.h"
#include "Map.h"
#include "Player.h"
#include "PlayerCard.h"

// Represents the state of the game
class GameState
{
public:
	GameState();
	const std::vector<std::unique_ptr<Player>>& players() const;
	Map& map() const;
	void addPlayer(std::unique_ptr<Player> player);
	void setMap(std::unique_ptr<Map> map);
	virtual bool shouldQuit() const;

	// Quits at the end of the current action frame.
	void quit();

	Player& nextPlayer();
	Player& currentPlayer();
	Player& setCurrentPlayer(const size_t idx);

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

	void advanceOutbreakCounter();
	CubePool& cubePool();

	Deck<PlayerCard>& playerDeck();
	Deck<InfectionCard>& infectionDeck();

private:
	std::unique_ptr<Map> _map;
	std::vector<std::unique_ptr<Player>> _players;
	size_t _currentPlayerIdx = std::numeric_limits<size_t>::max();
	CubePool _cubePool;
	std::map<Colour, bool> _cured;
	unsigned _infectionCounter = 1;
	unsigned _outbreakCounter = 0;
	bool _shouldQuit = false;
	unsigned _researchStations = 6;
	Deck<PlayerCard> _playerDeck;
	Deck<InfectionCard> _infectionDeck;
};

std::unique_ptr<GameState> quitState();