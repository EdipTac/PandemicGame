#pragma once

#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "MenuOption.h"
#include "City.h"
#include "Util.h"

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

	// Sets the message for coliciting user input
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

template <typename T>
Menu<T>::Menu(const std::vector<MenuOption<T>>& options)
	: _options { std::move(options) }
{}

template<typename T>
void Menu<T>::setMessage(const std::string& message)
{
	_message = message;
}

template <typename T>
void Menu<T>::addOption(const MenuOption<T>& option)
{
	_options.push_back(option);
}

template <typename T>
T Menu<T>::solicitInput() const
{
	std::cout << string();
	const auto idx = solicitSize(1, _options.size());
	std::cout << "\n";
	return _options[idx - 1].action();
}

template <typename T>
std::string Menu<T>::string() const
{
	std::stringstream ss;
	ss << _message << "\n";
	for (size_t i = 0; i < _options.size(); ++i)
	{
		ss << "\t(" << (i + 1) << ") " << _options[i].text << "\n";
	}
	ss << ": ";
	return ss.str();
}
