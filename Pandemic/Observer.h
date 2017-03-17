/*
This is the header file for the observer class
*/

#pragma once

class Observable; //the observable interface

class Observer
{
public:
	virtual ~Observer() {}; //a virtual destructor for the observer class
	virtual void update() = 0; //this method is what will be called by the notify function inside the observable class

protected:
	Observer() {};
};
