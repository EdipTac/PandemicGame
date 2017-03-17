#pragma once

#include <functional>
#include <vector>

class Observer;

class Observable
{
public:
	virtual ~Observable() = 0;
	void subscribe(Observer& observer);
	void unsubscribe(Observer& observer);
	void notify() const;

private:
	std::vector<Observer*> _observers;
};
