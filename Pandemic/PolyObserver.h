#pragma once

#include <algorithm>
#include <vector>

#include "Observer.h"

template <typename T>
class PolyObserver
	: public Observer
{
public:
	virtual ~PolyObserver() override = 0
	{
		for (const auto& subject : _subjects)
		{
			if (subject)
			{
				subject->unsubscribe(*this);
			}
		}
	}

	void subscribeTo(T& subject)
	{
		subject.subscribe(*this);
		_subjects.push_back(&subject);
	}

	void unsubscribeFrom(T& subject)
	{
		// Look for argument in list of subjects
		const auto& it = std::find_if(_subjects.begin(), _subjects.end(), [&](const auto& s)
		{
			return s == &subject;
		});

		// If it's not in the list, do nothing
		if (it == _subjects.end())
		{
			return;
		}

		// Otherwise unsubscribe this observer from the subject and delete from the list
		(*it)->unsubscribe(*this);
		_subjects.erase(it);
	}

protected:
	std::vector<T*> _subjects;
};
