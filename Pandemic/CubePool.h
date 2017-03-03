#pragma once

#include <map>

#include "Colour.h"

class CubePool
{
	using ColourCount = std::map<Colour, unsigned int>;

public:
	CubePool(const ColourCount& diseaseCubes);
	CubePool(const unsigned int cubesPerDisease);
	void giveTo(const Colour& colour, const unsigned int amount, CubePool& target);
	void takeFrom(const Colour& colour, const unsigned int amount, CubePool& target);

private:
	ColourCount _diseaseCubes;
};

