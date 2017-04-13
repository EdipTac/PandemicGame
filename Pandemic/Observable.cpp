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
	const auto& it = std::find_if(_observers.begin(), _observers.end(), [&](const auto& o)
	{
		return o == &observer;
	});
	if (it != _observers.end())
	{
		_observers.erase(it);
	}
}

void Observable::notify() const
{
	for (auto& observer : _observers)
	{
		observer->update();
	}
}
