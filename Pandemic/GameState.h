#pragma once

#include <vector>
#include <memory>

#include "Map.h"
#include "Player.h"

class GameState
{
public:
	const std::vector<std::unique_ptr<Player>>& players() const;
	Map& map() const;

	GameState& addPlayer(std::unique_ptr<Player> player);
	GameState& setMap(std::unique_ptr<Map> map);

private:
	std::unique_ptr<Map> _map;
	std::vector<std::unique_ptr<Player>> _players;
};

