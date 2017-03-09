#pragma once

#include <map>
#include <vector>
#include <string>

#include "GameState.h"
#include "Map.h"

// Utility functions for reading maps from and to a text file

// Returns a map read from a given text file
std::unique_ptr<Map> readMapFromFile(const std::string& fileName);

// Given a map and file name, writes the map as a text file
//void writeMapToFile(const Map& map, const std::string& fileName);

void readGameFromFile(const std::string& fileName);