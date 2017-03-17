#include <algorithm>

#include "DiseaseTracker.h"

TerminationState DiseaseTracker::terminationState() const
{
	using TS = TerminationState;
	return TS::InProgress;
}

bool DiseaseTracker::isCured(const Colour& colour) const
{
	return false;
}

void DiseaseTracker::cure(const Colour& colour)
{
}
