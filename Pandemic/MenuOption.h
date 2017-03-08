#pragma once

#include <functional>
#include <string>

template <typename T>
struct MenuOption
{
	using Action = std::function<T()>;
	std::string text;
	Action action;
};