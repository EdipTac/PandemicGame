#include <array>
#include <map>
#include <string>

#include "Colour.h"

struct ColourData
{
	const std::string name;
	const std::string abbreviation;
};

static const std::array<Colour, 4> _colours
{
	Colour::Black,
	Colour::Blue,
	Colour::Red,
	Colour::Yellow
};

static const std::map<Colour, ColourData> _colourData
{
	{ Colour::Black,  { "Black",  "K" } },
	{ Colour::Blue,   { "Blue",   "B" } },
	{ Colour::Red,    { "Red",    "R" } },
	{ Colour::Yellow, { "Yellow", "Y" } }
};

std::array<Colour, 4> colours()
{
	return _colours;
}

std::string colourName(const Colour& colour)
{
	return _colourData.at(colour).name;
}

std::string colourAbbreviation(const Colour& colour)
{
	return _colourData.at(colour).abbreviation;
}
