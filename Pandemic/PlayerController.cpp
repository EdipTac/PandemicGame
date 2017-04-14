#include "PlayerController.h"

std::vector<Player*> PlayerController::players()
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

void PlayerController::add(std::unique_ptr<Player> player)
{
	if (nameExists(player->name()))
	{
		throw std::logic_error { "No two players can have the same name." };
	}
	_players.push_back(std::move(player));
}

Player& PlayerController::next()
{
	++_currentPlayerIdx;
	_currentPlayerIdx %= _players.size();
	return current();
}

Player& PlayerController::current()
{
	return *_players[_currentPlayerIdx];
}

Player& PlayerController::setCurrent(const size_t idx)
{
	_currentPlayerIdx = idx % _players.size();
	return current();
}

bool PlayerController::nameExists(const std::string & name) const
{
	return std::any_of(_players.begin(), _players.end(), [&](const auto& p)
	{
		return p->name() == name;
	});
}

size_t PlayerController::size() const
{
	return _players.size();
}
