#include "Quit.h"

Quit::Quit(const std::string& msg)
	: _msg { msg }
{}

const char* Quit::what() const
{
	return _msg.c_str();
}
