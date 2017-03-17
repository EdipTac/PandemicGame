#include <algorithm>

#include "Observable.h"
#include "Observer.h"

Observable::~Observable() {}

void Observable::subscribe(Observer& observer)
{
	_observers.push_back(&observer);
}

void Observable::unsubscribe(Observer& observer)
{
	std::remove_if(_observers.begin(), _observers.end(), [&](const auto& o)
	{
		return o == &observer;
	});
}

void Observable::notify() const
{
	for (auto& observer : _observers)
	{
		observer->update();
	}
}
