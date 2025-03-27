#include "CenzoreTransformation.h"
#include "ReplaceTransformation.h"

CenzoreTransformation::CenzoreTransformation(std::string stringToCenzor, char cenzorWith)
	:stringToCenzor(std::move(stringToCenzor)), cenzorWith(cenzorWith) {}

const std::string& CenzoreTransformation::getStringToCenzor() const
{
	return this->stringToCenzor;
}

std::string CenzoreTransformation::transform(const std::string& text) const
{
	std::string textCopy = text;
	std::string toReplaceWith(this->stringToCenzor.size(), this->cenzorWith);

	size_t pos = 0;
	while ((pos = textCopy.find(this->stringToCenzor, pos)) != std::string::npos) {
		textCopy.replace(pos, this->stringToCenzor.length(), toReplaceWith);
		pos += toReplaceWith.length();
	}
	return textCopy;
}


bool CenzoreTransformation::operator==(const TextTransformation& other) const
{
	const CenzoreTransformation* castedOther = dynamic_cast<const CenzoreTransformation*>(&other);
	if (castedOther)
		return this->stringToCenzor == castedOther->stringToCenzor;
	return false;
}

std::string CenzoreTransformation::toString() const
{
	return "Cenzore( " + this->stringToCenzor + " )";
}

std::unique_ptr<TextTransformation> CenzoreTransformation::clone() const
{
	return std::make_unique<CenzoreTransformation>(this->stringToCenzor, this->cenzorWith);
}