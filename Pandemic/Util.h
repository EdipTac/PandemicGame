#pragma once

#include <functional>
#include <tuple>
#include <string>
#include <sstream>
#include <map>

#include "City.h"
#include "Map.h"

void clearStringStream(std::stringstream& ss);

std::pair<std::string, std::string> splitOnLastSpace(const std::string& s);

// True iff a file with the given name exists
bool fileExists(const std::string& fileName);

std::string getline(std::ifstream& fs);

bool lowercaseEquals(const std::string& a, const std::string& b);

std::string toLower(const std::string& s);

template<typename T>
std::map<std::string, T*> makeNameMap(const std::vector<T*>& entities)
{
	std::map<std::string, T*> map;
	for (const auto& e : entities)
	{
		map[e->name()] = e;
	}
	return map;
}

template <typename T>
T validateInput(const std::map<std::string, T>& valid, const std::string& errMsg)
{
	std::string input;
	decltype(valid.find(input)) it;
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		it = valid.find(input);
		if (it != valid.end())
		{
			break;
		}
		std::cout << errMsg;
	}
	return it->second;
}

template <typename T>
T validateInput(const std::vector<T>& valid, const std::string& errMsg)
{
	return validateInput(makeNameMap(valid), errMsg);
}

template <typename T>
void list(const T& collection)
{
	for (const auto& e : collection)
	{
		std::cout << "\t" << e->name() << "\n";
	}
}

std::string solicitLine(const std::string& msg = "");

void showCity(City& city);

City* solicitCity(const Map& map);
