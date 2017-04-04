#pragma once

#include <vector>

class Observer; //the abstract implementation for the subject component of the 

class Observable
{
public:
	Observable();
	virtual ~Observable() = 0;
	virtual void attach(Observer* observer);
	virtual void detach(Observer* observer);
	virtual void notify();

private:
	std::vector<Observer*> _observers;
};
