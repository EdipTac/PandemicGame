#pragma once

#include <map>

#include "Colour.h"

// Represents a collection of disease cubes of each colour.
class CubePool
{
	using ColourCount = std::map<Colour, unsigned int>;

public:
	// Constructs a CubePool with a uniform number of disease cubes per colour.
	CubePool(const unsigned int cubesPerDisease);

	// Give a given number of disease cubes of a given colour to another CubePool.
	void giveTo(const Colour& colour, const unsigned int amount, CubePool& target);

	// Take a given number of disease cubes of a given colour from another CubePool.
	void takeFrom(const Colour& colour, const unsigned int amount, CubePool& target);

private:
	// Holds the count of disease cubes of each colour.
	ColourCount _diseaseCubes;
};

