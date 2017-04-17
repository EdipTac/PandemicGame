#pragma once

#include <functional>
#include <string>
#include <vector>

#include "MenuOption.h"

template <typename T> class Menu;

using GeneralMenu = Menu<void>;

// Each attempted action returns true iff the action was completed successfully.
using ActionMenu = Menu<bool>;

// Represents a menu for player selection
template <typename T>
class Menu
{
	using Action = std::function<T()>;

public:
	// Constructs a menu from a list of options
	Menu<T>(const std::vector<MenuOption<T>>& options = {});

	void setMessage(const std::string& message);

	// Adds a new menu option	
	void addOption(const MenuOption<T>& option);

	// Solicit user input
	T solicitInput() const;

	// Returns options for display
	std::string string() const;

private:
	std::string _message = "Please select an option:";
	std::vector<MenuOption<T>> _options;
};
