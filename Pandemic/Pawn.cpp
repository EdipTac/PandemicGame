#include "Pawn.h"

// Default Constructor 
Pawn::Pawn() 
	: _city(""), _colour("") {}
// Constructor
Pawn::Pawn(std::string city, std::string colour)
	: _city(city), _colour(colour) {}

// Accessor for _city
std::string Pawn::city() const {
	return _city;
}
// Mutator for _city
void Pawn::setCity(std::string city) {
	this->_city = city;
}

// Accessor for _colour
std::string Pawn::colour() const {
	return _colour;
}
// Mutator for _colour
void Pawn::setColour(const std::string colour) {
	this->_colour = colour;
}

// Implementation of a function that converts a Pawn object into an informative string
std::string Pawn::toString() {
	return "Pawn: city=", _city, " colour=", _colour;
}