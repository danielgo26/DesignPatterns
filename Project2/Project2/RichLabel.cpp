#include "RichLabel.h"

RichLabel::RichLabel(std::string value, std::string color, std::string fontName, double fontSize)
	:value(std::move(value)), color(std::move(color)), fontName(std::move(fontName)), fontSize(fontSize) {};

const std::string& RichLabel::getColor() const
{
	return this->color;
}

const std::string& RichLabel::getFontName() const
{
	return this->fontName;
}

double RichLabel::getFontSize() const
{
	return this->fontSize;
}

void RichLabel::setColor(const std::string& color)
{
	this->color = color;
}

void RichLabel::setFontName(const std::string& fontName)
{
	this->fontName = fontName;
}

void RichLabel::setFontSize(double size)
{
	this->fontSize = size;
}

std::string RichLabel::getText() const
{
	return this->value;
}

bool RichLabel::operator==(const LabelImplementation& other) const
{
	const RichLabel* castedOther = dynamic_cast<const RichLabel*>(&other);
	if (castedOther)
		return this->value == castedOther->value && this->color == castedOther->color
		&& this->fontName == castedOther->fontName && this->fontSize == castedOther->fontSize;
	return false;
}

std::string RichLabel::toString() const
{
	return "Rich text";
}