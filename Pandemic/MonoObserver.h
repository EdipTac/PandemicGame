#pragma once

#include "Observer.h"

template <typename T>
class MonoObserver
	: public Observer
{
public:
	MonoObserver() {}

	MonoObserver(T& subject)
		: _subject { &subject }
	{}

	virtual ~MonoObserver() override  = 0 {}

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
