#pragma once

#include <vector>

class Observer; //the abstract implementation for the subject component of the 

class Observable
{
public:
	virtual ~Observable() = 0;
	void attach(Observer& observer);
	void detach(Observer& observer);
	void notify() const;

private:
	std::vector<Observer*> _observers;
};
