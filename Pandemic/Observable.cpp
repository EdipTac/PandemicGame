/*
This is the code segment to implement the observable class. The function implemented
are those are required to attach an observer, detach an observer,
and the notify method. The notify method is used as an updater to get the latest state
of the player class in this implementation
*/

#include <algorithm>

#include "Observable.h"
#include "Observer.h"

Observable::~Observable() {}

void Observable::attach(Observer& observer)
{
	_observers.push_back(&observer);
}

void Observable::detach(Observer& observer)
{
	std::remove_if(_observers.begin(), _observers.end(), [&](const auto& o)
	{
		return o == &observer;
	});
}

void Observable::notify() const
{
	for (auto& observer : _observers) // this is done to notify each of the observers present
	{
		observer->update();
	}
}
