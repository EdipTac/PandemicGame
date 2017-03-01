#pragma once

#include <array>
#include <string>

// Represents a colour of disease
enum class Colour
{
	Black,
	Blue,
	Red,
	Yellow
};

// Allows enumeration through all colour enum values
std::array<Colour, 4> colours();

// Returns a string representation of a colour enum value
std::string colourToString(const Colour& colour);
