#pragma once

#include <vector>

#include "Observer.h"

template <typename T>
class PolyObserver
	: public Observer
{
public:
	virtual ~PolyObserver() override  = 0 {}

	void subscribeTo(T& subject)
	{
		subject.subscribe(*this);
		_subjects.push_back(&subject);
	}

protected:
	std::vector<T*> _subjects;
};
