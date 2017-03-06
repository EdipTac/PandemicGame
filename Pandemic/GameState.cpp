#include "GameState.h"

GameState::GameState()
	: _cubePool { 96 / 4 }
{}

const std::vector<std::unique_ptr<Player>>& GameState::players() const
{
	return _players;
}

Map& GameState::map() const
{
	return *_map;
}

void GameState::addPlayer(std::unique_ptr<Player> player)
{
	_players.push_back(std::move(player));
}

void GameState::setMap(std::unique_ptr<Map> map)
{
	_map = std::move(map);
}
