#include "Label.h"

Label::Label(std::unique_ptr<LabelImplementation> label)
{
	if (!label)
		throw std::invalid_argument("Invalid label!");
	this->label = std::move(label);
}

std::string Label::getText() const
{
	return this->label->getText();
}

bool Label::operator==(const Label& other) const
{
	return this->label->operator==(*other.label);
}

std::string Label::toString() const
{
	return "Label with " + this->label->toString() + " value";
}