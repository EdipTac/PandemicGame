#include "CubePool.h"

CubePool::CubePool(const unsigned cubesPerDisease)
{
	for (const auto& colour : colours())
	{
		_diseaseCubes[colour] = cubesPerDisease;
		_diseasesCured[colour] = false;
		_diseasesEradicated[colour] = false;
	}
	

}

void CubePool::takeFrom(const Colour& colour, const unsigned amount, CubePool& target)
{
	const int trueAmount = std::min(target._diseaseCubes[colour], amount);
	target._diseaseCubes[colour] -= trueAmount;
	_diseaseCubes[colour] += trueAmount;
}

unsigned CubePool::operator[](const Colour& colour) const
{
	return _diseaseCubes.find(colour)->second;
}
bool CubePool::isEradicated(const Colour& colour) const
{
	return _diseasesEradicated.find(colour)->second;
}

void CubePool::giveTo(const Colour& colour, const unsigned amount, CubePool& target)
{
	const int trueAmount = std::min(_diseaseCubes[colour], amount);
	_diseaseCubes[colour] -= trueAmount;
	target._diseaseCubes[colour] += trueAmount;
}