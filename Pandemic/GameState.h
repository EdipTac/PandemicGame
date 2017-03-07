#pragma once

#include <vector>
#include <memory>

#include "CubePool.h"
#include "Map.h"
#include "Player.h"

// Represents the state of the game
class GameState
{
public:
	GameState();
	const std::vector<std::unique_ptr<Player>>& players() const;
	Map& map() const;
	void addPlayer(std::unique_ptr<Player> player);
	void setMap(std::unique_ptr<Map> map);
	bool shouldQuit() const;

	// Quits at the end of the current action frame.
	void quit();

	Player& nextPlayer();
	Player& currentPlayer() const;

	unsigned researchStations() const;
	void removeResearchStation();

private:
	bool _shouldQuit = false;
	std::unique_ptr<Map> _map;
	std::vector<std::unique_ptr<Player>> _players;
	size_t _currentPlayerIdx = std::numeric_limits<size_t>::max();
	CubePool _cubePool;
	unsigned _outbreakCounter;
	unsigned _researchStations = 6;
};

