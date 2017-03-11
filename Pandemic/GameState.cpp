#include <algorithm>
#include <vector>
#include <memory>

#include "GameState.h"

GameState::GameState()
	: _cubePool { 96 / 4 }
{
	for (const auto& colour : colours())
	{
		_cured[colour] = false;
	}
}

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

void GameState::returnResearchStation()
{
	++_researchStations;
}

bool GameState::hasResearchStation() const
{
	return _researchStations > 0;
}

void GameState::cure(const Colour& colour)
{
	_cured[colour] = true;
}

bool GameState::isCured(const Colour& colour) const
{
	return _cured.at(colour);
}

void GameState::advanceInfectionCounter()
{
	_infectionCounter = std::min(_infectionCounter + 1, 7u);
}

unsigned GameState::infectionRate() const
{
	const auto& c = _infectionCounter; // Alias
	return	(1 <= c && c <= 3)	? 2 :
			(4 <= c && c <= 5)	? 3 :
								  4 ;
}

void GameState::advanceOutbreakCounter()
{
	++_outbreakCounter;
	if (_outbreakCounter >= 8)
	{
		std::cout << "You lose! 8 outbreaks.\n";
		quit();
	}
}

CubePool& GameState::cubePool()
{
	return _cubePool;
}

Deck& GameState::playerDeck()
{
	return _playerDeck;
}

Deck& GameState::infectionDeck()
{
	return _infectionDeck;
}

class QuitState
	: public GameState
{
	bool shouldQuit() const override
	{
		return true;
	}
};

std::unique_ptr<GameState> quitState()
{
	return std::make_unique<QuitState>();
}