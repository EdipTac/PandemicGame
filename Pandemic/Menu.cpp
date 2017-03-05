#include <iostream>
#include <sstream>

#include "Menu.h"

Menu::Menu(const std::vector<MenuOption>& options)
	: _options { options }
{}

void Menu::addOption(const MenuOption& option)
{
	_options.push_back(option);
}

void Menu::solicitInput() const
{
	std::cout << string();
	int idx;
	while (true)
	{
		std::cin >> idx;
		std::cin.get();
		--idx;
		if (idx >= 0 && idx < _options.size())
		{
			break;
		}
		std::cout << "Not a valid option.\n";
	}
	_options[idx].action();
}

std::string Menu::string() const
{
	std::stringstream ss;
	ss << "Please select an option:\n";
	for (size_t i = 0; i < _options.size(); ++i)
	{
		ss << "\t(" << (i + 1) << ") " << _options[i].text << "\n";
	}
	ss << ": ";
	return ss.str();
}
