#include <algorithm>
#include <vector>
#include <memory>

#include "Board.h"
#include "TerminationHandler.h"

Board& Board::instance()
{
	static Board board;
	return board;
}

Board::Board()
	: _cubePool { 96 / 4 }
	, _terminationHandler { std::make_unique<TerminationHandler>() }
{
	_terminationHandler->subscribeTo(_outbreakCounter);
	_terminationHandler->subscribeTo(_diseaseTracker);
}

Board::~Board() {}

std::vector<Player*> Board::players()
{
	std::vector<Player*> p;
	const auto size = _players.size();
	auto idx = _currentPlayerIdx;
	for (auto i = 0u; i < size; ++i)
	{
		p.push_back(_players[idx].get());
		idx = (idx + 1) % size;
	}
	return p;
}

Map& Board::map() const
{
	return *_map;
}

void Board::addPlayer(std::unique_ptr<Player> player)
{
	if (nameExists(player->name()))
	{
		throw std::logic_error { "No two players can have the same name." };
	}
	_players.push_back(std::move(player));
	_handObserver.subscribeTo(*_players.back().get());
}

void Board::setMap(std::unique_ptr<Map> map)
{
	_map = std::move(map);
}

bool Board::shouldQuit() const
{
	return _terminationHandler->shouldQuit();
}

void Board::quit()
{
	_terminationHandler->quit();
}

Player& Board::nextPlayer()
{
	++_currentPlayerIdx;
	_currentPlayerIdx %= _players.size();
	return currentPlayer();
}

Player& Board::currentPlayer()
{
	return *_players[_currentPlayerIdx];
}

Player& Board::setCurrentPlayer(const size_t idx)
{
	_currentPlayerIdx = idx % _players.size();
	return currentPlayer();
}

bool Board::nameExists(const std::string& name) const
{
	return std::any_of(_players.begin(), _players.end(), [&](const auto& p)
	{
		return p->name() == name;
	});
}

unsigned Board::researchStations() const
{
	return _researchStations;
}

void Board::removeResearchStation()
{
	if (_researchStations == 0)
	{
		throw std::logic_error { "No research stations in pool." };
	}

	--_researchStations;
}

void Board::returnResearchStation()
{
	++_researchStations;
}

bool Board::hasResearchStation() const
{
	return _researchStations > 0;
}

void Board::cureDisease(const Colour& colour)
{
	_diseaseTracker.cure(colour);
}

bool Board::isCured(const Colour& colour) const
{
	return _diseaseTracker.isCured(colour);
}

bool Board::isEradicated(const Colour& colour) const
{
	return isCured(colour) && diseaseCount(colour) == 0;
}

size_t Board::diseaseCount(const Colour& colour) const
{
	size_t count = 0;
	for (const auto& city : _map->cities())
	{
		count += city->diseaseCubes(colour);
	}
	return count;
}

void Board::advanceInfectionCounter()
{
	_infectionCounter = std::min(_infectionCounter + 1, 7u);
}

unsigned Board::infectionRate() const
{
	const auto& c = _infectionCounter; // Alias
	return	(1 <= c && c <= 3) ? 2 :
			(4 <= c && c <= 5) ? 3 :
								 4 ;
}

unsigned Board::infectionCounter() const
{
	return _infectionCounter;
}
size_t Board::infectedCityCounter() const
{
	size_t count = 0;
	for (const auto& city : _map->cities())
	{
		if(city->isInfected())
		count ++;
	}
	return count;

}
size_t Board::outbreaks() const
{
	return _outbreakCounter.counter();
}

void Board::advanceOutbreakCounter()
{
	_outbreakCounter.advance();
}

CubePool& Board::cubePool()
{
	return _cubePool;
}

Deck<PlayerCard>& Board::playerDeck()
{
	return _playerDeck;
}

InfectionCardDeck& Board::infectionDeck()
{
	return _infectionDeck;
}

size_t Board::initialCards() const
{
	const auto size = _players.size();
	return	size <= 2 ? 4 :
			size == 3 ? 3 :
						2 ;
}

void Board::distributePlayerCards(const size_t count)
{
	for (auto i = 0u; !playerDeck().empty() && i < count; ++i)
	{
		currentPlayer().addCard(playerDeck().drawTopCard());
	}
}
