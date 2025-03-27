#include "CapitalizeTransformation.h"
#include <algorithm>

std::string CapitalizeTransformation::transform(const std::string& text) const
{
	std::string textCopy = text;
	if (!textCopy.empty() && textCopy[0] >= 'a' && textCopy[0] <= 'z')
		textCopy[0] = std::toupper(text[0]);
	return textCopy;
}

bool CapitalizeTransformation::operator==(const TextTransformation& other) const
{
	return dynamic_cast<const CapitalizeTransformation*>(&other);
}

std::string CapitalizeTransformation::toString() const
{
	return "Capitalize";
}

std::unique_ptr<TextTransformation> CapitalizeTransformation::clone() const
{
	return std::make_unique<CapitalizeTransformation>();
}