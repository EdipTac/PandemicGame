#include <array>
#include <map>

#include "Colour.h"

static const std::array<Colour, 4> _colours
{
	Colour::Black,
	Colour::Blue,
	Colour::Red,
	Colour::Yellow
};

static const std::map<Colour, std::string> _colourStrings
{
	{ Colour::Black,  "Black"  },
	{ Colour::Blue,   "Blue"   },
	{ Colour::Red,    "Red"    },
	{ Colour::Yellow, "Yellow" }
};

std::array<Colour, 4> colours()
{
	return _colours;
}

std::string colourToString(const Colour & colour)
{
	return _colourStrings.at(colour);
}
