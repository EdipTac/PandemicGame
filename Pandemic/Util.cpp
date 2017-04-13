#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>

#include "Util.h"

void clearStringStream(std::stringstream& ss)
{
	ss.str("");
	ss.clear();
}

std::pair<std::string, std::string> splitOnLastSpace(const std::string& s)
{
	auto it = s.end() - 1;
	for (; it != s.begin(); --it)
	{
		if (*it == ' ')
		{
			break;
		}
	}
	return { { s.begin(), it }, { it + 1, s.end() } };
}

bool fileExists(const std::string& fileName)
{
	return std::fstream { fileName }.good();
}

std::string getline(std::ifstream& fs)
{
	std::string line;
	std::getline(fs, line);
	return line;
}

bool lowercaseEquals(const std::string& a, const std::string& b)
{
	return toLower(a) == toLower(b);
}

std::string stringTransform(const std::string& original, const std::function<char(char)>& f)
{
	auto copy = original;
	std::transform(copy.begin(), copy.end(), copy.begin(), f);
	return copy;
}

std::string toLower(const std::string& original)
{
	return stringTransform(original, ::tolower);
}

std::string solicitLine(const std::string& msg)
{
	std::cout << msg;
	std::string string;
	std::getline(std::cin >> std::ws, string);
	return string;
}

City* solicitCity(const Map& map)
{
	if (map.cities().empty())
	{
		std::cout << "No cities.\n";
		return nullptr;
	}
	City* city = nullptr;
	std::cout << "Enter city name: ";
	while (true)
	{
		city = map.findCityIfContained(solicitLine());
		if (city)
		{
			break;
		}
		std::cout << "No city by that name.\n";
	}
	return city;
}

void showCity(City& city)
{
	std::cout << city.string();
}

std::string solicitFileName(const std::string& msg)
{
	std::string fileName;
	while (true)
	{
		std::cout << msg;
		std::cin >> fileName;
		std::cin.get();
		if (fileExists(fileName))
		{
			break;
		}
		std::cout << "File not found.\n";
	}
	return fileName;
}

std::string rightPad(const std::string& original, const size_t width)
{
	std::stringstream ss;
	ss << original;
	for (auto i = original.size(); i < width; ++i)
	{
		ss << " ";
	}
	return ss.str();
}

std::string titleFont(const std::string& original)
{
	std::stringstream ss;
	const auto& repeat = [&](const char c, const size_t t)
	{
		for (size_t i = 0; i < t; ++i)
		{
			ss << c;
		}
	};
	const auto& ornament = [&]()
	{
		repeat(' ', 4);
		repeat('-', 8);
		repeat(' ', 4);
	};
	const auto& insertSpaces = [&]()
	{
		for (auto it = original.begin(); it != original.end(); ++it)
		{
			ss << *it;
			if (it == original.end() - 1)
			{
				break;
			}
			ss << ' ';
		}
	};

	ornament();
	insertSpaces();
	ornament();

	return ss.str();
}
