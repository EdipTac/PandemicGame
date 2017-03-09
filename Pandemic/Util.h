#pragma once

#include <functional>
#include <tuple>
#include <string>
#include <sstream>
#include <map>

#include "City.h"

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
