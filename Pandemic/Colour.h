#pragma once

#include <array>
#include <string>
#include <map>

// Represents a colour of disease
enum class Colour
{
	Black,
	Blue,
	Red,
	Yellow
};

// Allows enumeration through all colour values
std::array<Colour, 4> colours();

// Returns a string representation of a colour enum value
std::string colourName(const Colour& colour);

// Colour abbreviation
std::string colourAbbreviation(const Colour& colour);

// Make colour from name
Colour colourFromName(const std::string& name);

// Make colour from abbreviation
Colour colourFromAbbreviation(const std::string& abbreviation);

std::map<std::string, Colour> colourNameMap();
