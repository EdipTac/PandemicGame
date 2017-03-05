#pragma once

#include <functional>
#include <string>

struct MenuOption
{
	using Action = std::function<void()>;
	std::string text;
	Action action;
};