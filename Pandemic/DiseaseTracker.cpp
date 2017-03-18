#include <algorithm>

#include "DiseaseTracker.h"

TerminationState DiseaseTracker::terminationState() const
{
	using TS = TerminationState;
	for (const auto& colour : colours())
	{
		if (!isCured(colour))
		{
			return TS::InProgress;
		}
	}
	return TS::Victory;
}

bool DiseaseTracker::isCured(const Colour& colour) const
{
	return _cured.find(colour) != _cured.end();
}

void DiseaseTracker::cure(const Colour& colour)
{
	_cured.insert(colour);
}
