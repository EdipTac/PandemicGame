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
	_terminationHandler->subscribeTo(_playerDeck);
}

Board::~Board() {}

std::vector<Player*> Board::players()
{
	return _playerController.players();
}

Map& Board::map() const
{
	return *_map;
}

void Board::addPlayer(std::unique_ptr<Player> player)
{
	_handObserver.subscribeTo(*player.get());
	_playerController.add(std::move(player));
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

void Board::nextPlayer()
{
	_playerController.next();
}

Player& Board::currentPlayer()
{
	return _playerController.current();
}

Player& Board::setCurrentPlayer(const size_t idx)
{
	return _playerController.setCurrent(idx);
}

bool Board::nameExists(const std::string& name) const
{
	return _playerController.nameExists(name);
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

void Board::setOutbreakCounter(int counter)
{
	_outbreakCounter.setCounter(counter);
}

CubePool& Board::cubePool()
{
	return _cubePool;
}

PlayerCardDeck& Board::playerDeck()
{
	return _playerDeck;
}

Deck<InfectionCard>& Board::infectionDeck()
{
	return _infectionDeck;
}

size_t Board::initialCards() const
{
	const auto size = _playerController.size();
	return	size <= 2 ? 4 :
			size == 3 ? 3 :
						2 ;
}

void Board::distributePlayerCards(const size_t count)
{    
	currentPlayer().drawFrom(_playerDeck, count);
}
