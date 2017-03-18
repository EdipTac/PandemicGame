#pragma once

#include "Observer.h"

template <typename T>
class View
	: public Observer
{
public:
	View() {}

	View(T& subject)
		: _subject { &subject }
	{}

	virtual ~View() override  = 0 {}

	void subscribeTo(T& subject)
	{
		if (_subject)
		{
			if (_subject == &subject)
			{
				return;
			}
			_subject->unsubscribe(*this);
		}
		_subject = &subject;
	}

private:
	T* _subject;
};
