#include <iostream>
#include <sstream>

#include "City.h"
#include "Menu.h"
#include "Util.h"

template class Menu<void>;
template class Menu<bool>;
template class Menu<City*>;

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
