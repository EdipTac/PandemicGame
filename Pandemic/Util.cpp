#include "Util.h"

#include <sstream>

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
