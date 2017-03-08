#include <iostream>
#include <sstream>

#include "Menu.h"

template <typename T>
Menu<T>::Menu(const std::vector<MenuOption<T>>& options)
	: _options { std::move(options) }
{}

template <typename T>
void Menu<T>::addOption(const MenuOption<T>& option)
{
	_options.push_back(option);
}

template <typename T>
T Menu<T>::solicitInput() const
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
	return _options[idx].action();
}

template <typename T>
std::string Menu<T>::string() const
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

template class Menu<void>;
template class Menu<bool>;
