#include "ReplaceTransformation.h"

ReplaceTransformation::ReplaceTransformation(std::string stringToBeReplaced, std::string stringToReplaceWith)
	:stringToBeReplaced(std::move(stringToBeReplaced)), stringToReplaceWith(std::move(stringToReplaceWith)) {}

const std::string& ReplaceTransformation::getStringToBeReplaced() const
{
	return this->stringToBeReplaced;
}

const std::string& ReplaceTransformation::getStringToReplaceWith() const
{
	return this->stringToReplaceWith;
}

void ReplaceTransformation::setStringToBeReplaced(const std::string& stringToBeReplaced)
{
	this->stringToBeReplaced = stringToBeReplaced;
}

void ReplaceTransformation::setStringToReplaceWith(const std::string& stringToReplaceWith)
{
	this->stringToReplaceWith = stringToReplaceWith;
}

std::string ReplaceTransformation::transform(const std::string& text) const
{
	size_t pos = 0;
	std::string textCopy = text;

	while ((pos = textCopy.find(this->stringToBeReplaced, pos)) != std::string::npos) {
		textCopy.replace(pos, this->stringToBeReplaced.length(), this->stringToReplaceWith);
		pos += this->stringToReplaceWith.length();
	}

	return textCopy;
}

bool ReplaceTransformation::operator==(const TextTransformation& other) const
{
	const ReplaceTransformation* castedOther = dynamic_cast<const ReplaceTransformation*>(&other);
	if (castedOther)
		return this->stringToBeReplaced == castedOther->stringToBeReplaced &&
		this->stringToReplaceWith == castedOther->stringToReplaceWith;
	return false;
}

std::string ReplaceTransformation::toString() const
{
	return "Replace( " + this->stringToBeReplaced + ", " + this->stringToReplaceWith + " )";
}

std::unique_ptr<TextTransformation> ReplaceTransformation::clone() const
{
	return std::make_unique<ReplaceTransformation>(this->stringToBeReplaced, this->stringToReplaceWith);
}