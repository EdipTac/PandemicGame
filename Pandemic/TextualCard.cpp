#include "TextualCard.h"


TextualCard::TextualCard(std::string name, std::string description)
	: _name { name }
	, _description { description }
{}

TextualCard::~TextualCard()
{}

std::string TextualCard::name() const
{
	return _name;
}

std::string TextualCard::description() const
{
	return _description;
}

void TextualCard::setName(const std::string& name)
{
	_name = name;
}

void TextualCard::setDescription(const std::string& description)
{
	_description = description;
}
