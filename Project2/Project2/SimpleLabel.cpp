#include "SimpleLabel.h"

SimpleLabel::SimpleLabel(std::string value)
	:value(std::move(value)) {}

std::string SimpleLabel::getText() const
{
	return this->value;
}

bool SimpleLabel::operator==(const LabelImplementation& other) const
{
	const SimpleLabel* castedOther = dynamic_cast<const SimpleLabel*>(&other);
	if (castedOther)
		return this->value == castedOther->value;
	return false;
}

std::string SimpleLabel::toString() const
{
	return "Simple text";
}