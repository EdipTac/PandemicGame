#pragma once

#include <functional>
#include <string>
#include <vector>

#include "MenuOption.h"

// Represents a menu for player selection
class Menu
{
	using Action = std::function<void()>;

public:
	// Constructs a menu from a list of options
	Menu(const std::vector<MenuOption>& options);

	// Adds a new menu option	
	void addOption(const MenuOption& option);

	// Solicit user input
	void solicitInput() const;

	// Returns options for display
	std::string string() const;

private:
	std::vector<MenuOption> _options;
};
