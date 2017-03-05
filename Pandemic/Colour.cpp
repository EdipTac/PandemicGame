#include <array>
#include <map>
#include <string>

#include "Colour.h"

struct ColourData
{
public:
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

Colour _colourFromField(const std::string ColourData::* const field, const std::string& s)
{
	for (const auto& c : _colourData)
	{
		if (c.second.*field == s)
		{
			return c.first;
		}
	}
	throw std::logic_error { "No matching colour attribute." };
	return Colour::Black;
}

Colour colourFromName(const std::string& name)
{
	return _colourFromField(&ColourData::name, name);
}

Colour colourFromAbbreviation(const std::string& abbreviation)
{
	return _colourFromField(&ColourData::abbreviation, abbreviation);
}
