#pragma once

#include <tuple>
#include <string>
#include <sstream>

void clearStringStream(std::stringstream& ss);

std::pair<std::string, std::string> splitOnLastSpace(const std::string& s);
