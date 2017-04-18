#include <memory>
#include <string>

#include "MapEditor.h"
#include "Map.h"
#include "Menu.h"
#include "BoardBuilder.h"
#include "Util.h"
#include "Quit.h"

void addCity();
void deleteCity();
void listCities();
void editCity();
void loadMap();
void saveMap();
void cityReport(City& city);
void addConnection(City& city);
void deleteConnection(City& city);
void createNewMap();

std::unique_ptr<Map> map;

const GeneralMenu mapEditorMainMenu
{
	{
		{ "Create New Map", createNewMap	      },
		{ "Load Map",		loadMap			      },
		{ "Quit",			[](){ throw Quit(); } },
	}
};

const GeneralMenu editMapMenu
{
	{
		{ "Add City",    addCity               },
		{ "Delete City", deleteCity            },
		{ "List Cities", listCities            },
		{ "Edit City",   editCity              },
		{ "Save Map",    saveMap               },
		{ "Quit",        [](){ throw Quit(); } },
	}
};

void mapEditor()
{
	mapEditorMainMenu.solicitInput();
	while (map)
	{
		editMapMenu.solicitInput();
	}
}

void createNewMap()
{
	map = std::make_unique<Map>();
	map->name() = solicitLine("Enter map name: ");
}

void addCity()
{
	auto city = std::make_unique<City>();
	city->name() = solicitLine("Enter city name: ");
	std::cout << "Enter city colour: ";
	city->colour() = validateInput(colourNameMap(), "Not a colour.\n");
	if (map->cities().size() == 0)
	{
		map->startingCity() = city.get();
	}
	map->addCity(std::move(city));
}

void editCity()
{
	const auto& city = solicitCity(*map);
	if (city)
	{
		GeneralMenu
		{
			{
				{ "Report",				[&]() { cityReport(*city);			}	},
				{ "Add Connection",		[&]() { addConnection(*city);		}	},
				{ "Delete Connection",	[&]() { deleteConnection(*city);	}	}
			}
		}.solicitInput();
	}
}

void deleteCity()
{
	const auto city = solicitCity(*map);
	if (city)
	{
		map->removeCity(*city);
	}
}

void listCities()
{
	for (const auto& city : map->cities())
	{
		std::cout << "\t" << city->name() << ": " << colourName(city->colour()) << "\n";
	}
}

void cityReport(City& city)
{
	std::cout << city.string();
	if (map->startingCity() == &city)
	{
		std::cout << "*Starting city*\n\n";
	}
}

void addConnection(City& city)
{
	std::cout << "Where to connect to? ";
	auto target = solicitCity(*map);
	if (target)
	{
		city.connectTo(*target);
		target->connectTo(city);
	}
}

void deleteConnection(City& city)
{
	std::cout << "Which city to disconnect from? ";
	auto target = solicitCity(*map);
	if (target)
	{
		city.disconnectFrom(*target);
	}
}

void loadMap()
{
	const auto fileName = solicitFileName("Enter name of map file: ");
	map = readMapFromFile(fileName);
}

void saveMap()
{
	std::cout << "File name: ";
	std::string fileName;
	std::getline(std::cin >> std::ws, fileName);
	writeMapToFile(*map, fileName);
	std::cout << "Map saved!\n";
}
