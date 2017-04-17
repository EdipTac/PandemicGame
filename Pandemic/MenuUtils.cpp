#include "MenuUtils.h"

Menu<City*> cityMenu(const std::vector<City*>& cities)
{
	Menu<City*> menu;
	for (const auto& city : cities)
	{
		menu.addOption({ city->name(), [=]() { return city; } });
	}
	menu.addOption({ "Back", [](){ return nullptr; } });
	return menu;
}
