#pragma once

#include <vector>

#include "Menu.h"

// Makes a menu from a vector of pointer. The label for each option is given by function f applied to each element.
template <typename T, typename F>
Menu<T> makeMenu(const std::vector<T>& vector, F f)
{
	Menu<T> menu;
	for (const auto& element : vector)
	{
		menu.addOption({ f(element), [=]() { return element; } });
	}
	menu.addOption({ "Back", []() { return nullptr; } });
	return menu;
}

// As makeMenu, but the function defaults to calling the name() member of the type
template <typename T>
Menu<T> namedMenu(const std::vector<T>& vector)
{
	return makeMenu(vector, [](const auto& e) { return e->name(); });
}
