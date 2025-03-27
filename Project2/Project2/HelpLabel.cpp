#include "HelpLabel.h"

HelpLabel::HelpLabel(std::unique_ptr<LabelImplementation> label, std::string helpText)
	:Label(std::move(label)), helpText(std::move(helpText)) {}

const std::string& HelpLabel::getHelpText() const
{
	return this->helpText;
}

void HelpLabel::setHelpText(const std::string& helpText)
{
	this->helpText = helpText;
}

std::string HelpLabel::getText() const
{
	return this->label->getText();
}

bool HelpLabel::operator==(const Label& other) const
{
	const HelpLabel* castedOther = dynamic_cast<const HelpLabel*>(&other);
	if (castedOther)
		return this->helpText == castedOther->helpText && this->label->operator==(*castedOther->label.get());
	return false;
}

std::string HelpLabel::toString() const
{
	return "Help Label with " + this->label->toString() + " value";
}