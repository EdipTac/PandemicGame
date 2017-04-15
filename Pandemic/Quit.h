#pragma once

#include <stdexcept>
#include <string>

class Quit
	: public std::exception
{
public:
	Quit(const std::string& msg = "");
	virtual const char* what() const override;

private:
	std::string _msg;
};
