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
	const std::vector<std::unique_ptr<Player>>& players() const;
	Map& map() const;

	void addPlayer(std::unique_ptr<Player> player);
	void setMap(std::unique_ptr<Map> map);

private:
	std::unique_ptr<Map> _map;
	std::vector<std::unique_ptr<Player>> _players;
	CubePool _cubePool;
	// Deck
};

