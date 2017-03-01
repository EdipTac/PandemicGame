#include "GameState.h"

const std::vector<std::unique_ptr<Player>>& GameState::players() const
{
	return _players;
}

Map& GameState::map() const
{
	return *_map;
}

GameState& GameState::addPlayer(std::unique_ptr<Player> player)
{
	_players.push_back(std::move(player));
	return *this;
}

GameState& GameState::setMap(std::unique_ptr<Map> map)
{
	_map = std::move(map);
	return *this;
}
