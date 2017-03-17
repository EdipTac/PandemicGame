#pragma once

class Observable;

class Observer
{
public:
	virtual ~Observer() {};
	virtual void update() = 0;

protected:
	Observer() {};
};
