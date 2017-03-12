#pragma once

#include <map>

#include "Colour.h"

// Represents a collection of disease cubes of each colour.
class CubePool
{
public:
	// Constructs a CubePool with a uniform number of disease cubes per colour.
	CubePool(const unsigned cubesPerDisease);

	CubePool(const std::map<Colour, size_t>& cubes);

	// Give a given number of disease cubes of a given colour to another CubePool.
	void giveTo(const Colour& colour, const size_t amount, CubePool& target);

	// Take a given number of disease cubes of a given colour from another CubePool.
	void takeFrom(const Colour& colour, const size_t amount, CubePool& target);

	// The number of cubes of a given colour
	size_t& operator[](const Colour& colour);
	// The eradication boolean of a given colour
	bool isEradicated (const Colour& colour) const;
	

private:
	// Holds the count of disease cubes of each colour.
	std::map<Colour, size_t> _diseaseCubes;
	// Holds the cured boolean of each colour
	std::map<Colour, bool> _diseasesCured;
	// Holds the eradicated boolean of each colour
	std::map<Colour, bool> _diseasesEradicated;
};

