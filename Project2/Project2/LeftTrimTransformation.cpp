#include "LeftTrimTransformation.h"

std::string LeftTrimTransformation::transform(const std::string& text) const
{
	std::size_t startIndex = 0;

	while (startIndex < text.size() && std::isspace(text[startIndex])) {
		startIndex++;
	}

	return text.substr(startIndex);
}

bool LeftTrimTransformation::operator==(const TextTransformation& other) const
{
	return dynamic_cast<const LeftTrimTransformation*>(&other);
}

std::string LeftTrimTransformation::toString() const
{
	return "Left trim";
}

std::unique_ptr<TextTransformation> LeftTrimTransformation::clone() const
{
	return std::make_unique<LeftTrimTransformation>();
}