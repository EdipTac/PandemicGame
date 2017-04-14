#pragma once

#include <memory>
#include <vector>

#include "Player.h"

class PlayerController
{
public:
	std::vector<Player*> players();
	void add(std::unique_ptr<Player> player);
	Player& next();
	Player& current();
	Player& setCurrent(const size_t idx);
	bool nameExists(const std::string& name) const;
	size_t size() const;

private:
	std::vector<std::unique_ptr<Player>> _players;
	size_t _currentPlayerIdx = 0;
};
