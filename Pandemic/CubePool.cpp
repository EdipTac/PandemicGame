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

CubePool::CubePool(const std::map<Colour, size_t>& cubes)
	: _diseaseCubes { cubes }
{}

void CubePool::takeFrom(const Colour& colour, const size_t amount, CubePool& target)
{
	const size_t trueAmount = std::min(target._diseaseCubes[colour], amount);
	target._diseaseCubes[colour] -= trueAmount;
	_diseaseCubes[colour] += trueAmount;
}

size_t CubePool::operator[](const Colour& colour) const
{
	const auto& it = _diseaseCubes.find(colour);
	return it == _diseaseCubes.end() ? 0u : it->second;
}

size_t& CubePool::operator[](const Colour& colour)
{
	return _diseaseCubes[colour];
}
bool CubePool::isEradicated(const Colour& colour) const
{
	return _diseasesEradicated.find(colour)->second;
}

TerminationState CubePool::terminationState() const
{
	return _cubesLeft ? TerminationState::InProgress : TerminationState::Defeat;
}

std::string CubePool::message() const
{
	return "No cubes left to distribute.";
}

void CubePool::giveTo(const Colour& colour, const size_t amount, CubePool& target)
{
	const size_t trueAmount = std::min(_diseaseCubes[colour], amount);
	if (trueAmount > amount)
	{
		_cubesLeft = false;
	}
	_diseaseCubes[colour] -= trueAmount;
	target._diseaseCubes[colour] += trueAmount;
	notify();
}