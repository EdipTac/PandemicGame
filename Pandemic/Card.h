#pragma once

#include <string>

class Card
{
public:
	virtual ~Card();
	virtual std::string name() const = 0;
	virtual std::string description() const = 0;
};