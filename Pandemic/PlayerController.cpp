#include "PlayerController.h"

std::vector<Player*> PlayerController::players()
{
	std::vector<Player*> p;
	const auto size = _players.size();
	auto idx = _idx;
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
		throw std::invalid_argument("No two players can have the same name.");
	}
	_players.push_back(std::move(player));
}

Player& PlayerController::next()
{
	++_idx;
	_idx %= _players.size();
	return current();
}

Player& PlayerController::current()
{
	return *_players[_idx];
}

Player& PlayerController::setCurrent(const size_t idx)
{
	if (!(0 <= idx && idx < _players.size()))
	{
		throw std::invalid_argument("Invalid player index.");
	}
	_idx = idx;
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
