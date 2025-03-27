#include "DecorateTransformation.h"

std::string DecorateTransformation::transform(const std::string& text) const
{
	return "-={ " + text + " }=-";
}

bool DecorateTransformation::operator==(const TextTransformation& other) const
{
	return dynamic_cast<const DecorateTransformation*>(&other);
}

std::string DecorateTransformation::toString() const
{
	return "Decorate";
}

std::unique_ptr<TextTransformation> DecorateTransformation::clone() const
{
	return std::make_unique<DecorateTransformation>();
}