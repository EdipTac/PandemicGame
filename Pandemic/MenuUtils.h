#pragma once

#include <vector>

#include "Menu.h"

template <typename T>
Menu<T> namedMenu(const std::vector<T>& vector)
{
	Menu<T> menu;
	for (const auto& element : vector)
	{
		menu.addOption({ element->name(), [=]() { return element; } });
	}
	menu.addOption({ "Back", []() { return nullptr; } });
	return menu;
}
