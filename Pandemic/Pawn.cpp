#include "Pawn.h"

Pawn::Pawn() 
	: _city(""), _colour("") {}
Pawn::Pawn(std::string city, std::string colour)
	: _city(city), _colour(colour) {}

std::string Pawn::getCity() const {
	return _city;
}
void Pawn::setCity(std::string city) {
	this->_city = city;
}
std::string Pawn::getColour() const {
	return _colour;
}
void Pawn::setColour(const std::string colour) {
	this->_colour = colour;
}

std::string Pawn::toString() {
	return "Pawn: city=", _city, " colour=", _colour;
}