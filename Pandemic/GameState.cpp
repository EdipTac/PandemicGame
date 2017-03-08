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

bool GameState::shouldQuit() const
{
	return _shouldQuit;
}

void GameState::quit()
{
	_shouldQuit = true;
}

Player& GameState::nextPlayer()
{
	if (_currentPlayerIdx >= std::numeric_limits<size_t>::max())
	{
		_currentPlayerIdx = 0;
	}
	else
	{
		++_currentPlayerIdx;
		_currentPlayerIdx %= _players.size();
	}
	return currentPlayer();
}

Player& GameState::currentPlayer()
{
	return *_players[_currentPlayerIdx];
}

unsigned GameState::researchStations() const
{
	return _researchStations;
}

void GameState::removeResearchStation()
{
	if (_researchStations == 0)
	{
		throw std::logic_error { "No research stations in pool." };
	}

	--_researchStations;
}

bool GameState::hasResearchStation() const
{
	return _researchStations > 0;
}
