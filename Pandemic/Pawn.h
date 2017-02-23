#pragma once
#include <string>

class Pawn {
private:
	// Attributes for Pawn objects
	std::string _city;
	std::string _colour;

public:
	// Default Constructor
	Pawn();
	// Constructor
	Pawn(std::string city, std::string colour);

	// Accessor and Mutator for _city
	std::string city() const;
	void setCity(std::string city);

	// Accessor and Mutator for _colour
	std::string colour() const;
	void setColour(const std::string colour);

	// Function that converts a Pawn object into an informative string
	std::string toString();
};