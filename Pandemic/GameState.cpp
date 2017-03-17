#include <algorithm>
#include <vector>
#include <memory>

#include "GameState.h"

GameState::GameState()
	: _cubePool { 96 / 4 }
	, _terminationObserver { *this }
{
	for (const auto& colour : colours())
	{
		_cured[colour] = false;
	}
	_terminationObserver.subscribeTo(_outbreakCounter_);
}

std::vector<Player*> GameState::players()
{
	std::vector<Player*> p;
	const auto size = _players.size();
	if (_currentPlayerIdx >= std::numeric_limits<size_t>::max())
	{
		_currentPlayerIdx = 0;
	}
	auto idx = _currentPlayerIdx;
	for (auto i = 0u; i < size; ++i)
	{
		p.push_back(_players[idx].get());
		idx = (idx + 1) % size;
	}
	return p;
}

Map& GameState::map() const
{
	return *_map;
}

void GameState::addPlayer(std::unique_ptr<Player> player)
{
	if (nameExists(player->name()))
	{
		throw std::logic_error { "No two players can have the same name." };
	}
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
	/*if (_currentPlayerIdx >= std::numeric_limits<size_t>::max())
	{
		_currentPlayerIdx = 0;
	}*/
	return *_players[_currentPlayerIdx];
}

Player& GameState::setCurrentPlayer(const size_t idx)
{
	_currentPlayerIdx = idx % _players.size();
	return currentPlayer();
}

bool GameState::nameExists(const std::string& name) const
{
	return std::any_of(_players.begin(), _players.end(), [&](const auto& p)
	{
		return p->name() == name;
	});
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

void GameState::cureDisease(const Colour& colour)
{
	_cured[colour] = true;
}

bool GameState::isCured(const Colour& colour) const
{
	return _cured.at(colour);
}

bool GameState::isEradicated(const Colour& colour) const
{
	return isCured(colour) && diseaseCount(colour) == 0;
}

size_t GameState::diseaseCount(const Colour& colour) const
{
	size_t count = 0;
	for (const auto& city : _map->cities())
	{
		count += city->diseaseCubes(colour);
	}
	return count;
}

void GameState::advanceInfectionCounter()
{
	_infectionCounter = std::min(_infectionCounter + 1, 7u);
}

unsigned GameState::infectionRate() const
{
	const auto& c = _infectionCounter; // Alias
	return	(1 <= c && c <= 3) ? 2 :
			(4 <= c && c <= 5) ? 3 :
								 4 ;
}

unsigned GameState::infectionCounter() const
{
	return _infectionCounter;
}

size_t GameState::outbreakCounter() const
{
	return _outbreakCounter_.counter();
}

void GameState::advanceOutbreakCounter()
{
	_outbreakCounter_.advance();
}

CubePool& GameState::cubePool()
{
	return _cubePool;
}

Deck<PlayerCard>& GameState::playerDeck()
{
	return _playerDeck;
}

Deck<InfectionCard>& GameState::infectionDeck()
{
	return _infectionDeck;
}

size_t GameState::initialCards() const
{
	const auto size = _players.size();
	return	size <= 2 ? 4 :
			size == 3 ? 3 :
						2 ;
}

void GameState::distributePlayerCards(const size_t count)
{
	for (auto i = 0u; !playerDeck().empty() && i < count; ++i)
	{
		currentPlayer().addCard(playerDeck().drawTopCard());
	}
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