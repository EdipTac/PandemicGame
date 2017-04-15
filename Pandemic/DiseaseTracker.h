#pragma once

#include <set>

#include "Colour.h"
#include "Terminator.h"

class DiseaseTracker
	: public Terminator
{
public:
	virtual TerminationState terminationState() const override;
	virtual std::string message() const override;
	bool isCured(const Colour& colour) const;
	void cure(const Colour& colour);

private:
	std::set<Colour> _cured;
};
