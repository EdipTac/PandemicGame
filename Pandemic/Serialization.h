#pragma once

#include <map>
#include <vector>
#include <string>

#include "Map.h"

// Utility functions for reading maps from and to a text file

// True iff a file with the given name exists
bool fileExists(const std::string& fileName);

// Returns a map read from a given text file
std::unique_ptr<Map> readMapFromFile(const std::string& fileName);

// Given a map and file name, writes the map as a text file
void writeMapToFile(const Map& map, const std::string& fileName);
