#include "RightTrimTransformation.h"

std::string RightTrimTransformation::transform(const std::string& text) const
{
	std::size_t endIndex = text.size();

	while (endIndex > 0 && std::isspace(text[endIndex - 1])) {
		endIndex--;
	}

	return text.substr(0, endIndex);
}

bool RightTrimTransformation::operator==(const TextTransformation& other) const
{
	return dynamic_cast<const RightTrimTransformation*>(&other);
}

std::string RightTrimTransformation::toString() const
{
	return "Right trim";
}

std::unique_ptr<TextTransformation> RightTrimTransformation::clone() const
{
	return std::make_unique<RightTrimTransformation>();
}