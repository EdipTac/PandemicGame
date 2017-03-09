#include <algorithm>
#include <fstream>
#include <functional>
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
