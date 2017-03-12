#include <memory>
#include <string>

#include "MapEditor.h"
#include "Map.h"
#include "Menu.h"
#include "Util.h"

void addCity();
void deleteCity();
void listCities();
void createNewMap();

const GeneralMenu mapEditorMainMenu
{
	{
		{ "Create New Map", createNewMap }
	}
};

const GeneralMenu editMapMenu
{
	{
		{ "Add City",		addCity		},
		{ "Delete City",	deleteCity	},
		{ "List Cities",	listCities	}
	}
};

std::unique_ptr<Map> map;

void mapEditor()
{
	mapEditorMainMenu.solicitInput();
}

void createNewMap()
{
	map = std::make_unique<Map>();
	map->name() = solicitLine("Enter map name: ");
	while (true)
	{
		editMapMenu.solicitInput();
	}
}

void addCity()
{
	auto city = std::make_unique<City>();
	city->name() = solicitLine("Enter city name: ");
	std::cout << "Enter city colour: ";
	city->colour() = validateInput(colourNameMap(), "Not a colour.\n");
	map->addCity(std::move(city));
}

void deleteCity()
{
	if (map->cities().empty())
	{
		std::cout << "No cities.\n";
		return;
	}
	City* city = nullptr;
	std::cout << "Enter city name: ";
	while (true)
	{
		city = map->findCityIfContained(solicitLine());
		if (city)
		{
			break;
		}
		std::cout << "No city by that name.\n";
	}
	map->removeCity(*city);
}

void listCities()
{
	for (const auto& city : map->cities())
	{
		std::cout << "\t" << city->name() << ": " << colourName(city->colour()) << "\n";
	}
}
