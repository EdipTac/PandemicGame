#pragma once
#include <string>

class Pawn {
private:
	std::string _city;
	std::string _colour;

public:
	Pawn();
	Pawn(std::string city, std::string colour);

	std::string getCity() const;
	void setCity(std::string city);
	std::string getColour() const;
	void setColour(const std::string colour);

	std::string toString();
};