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

	virtual ~MonoObserver() override = 0
	{
		unsubscribe();
	}

	void subscribeTo(T& subject)
	{
		// If there is already a subject, unsubscribe this
		if (_subject)
		{
			if (_subject == &subject)
			{
				return;
			}
			_subject->unsubscribe(*this);
		}

		// Subscribe new subject
		_subject = &subject;
		_subject->subscribe(*this);
	}

	void unsubscribe()
	{
		if (_subject)
		{
			_subject->unsubscribe(*this);
			_subject = nullptr;
		}
	}

private:
	T* _subject;
};
