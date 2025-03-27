#include "CompositeTransformation.h"

CompositeTransformation::CompositeTransformation(std::vector<std::unique_ptr<TextTransformation>> transformations)
{
	for (size_t i = 0; i < transformations.size(); i++)
	{
		if (!transformations[i])
			throw std::invalid_argument("Invalid transformation!");
	}
	this->transformations = std::move(transformations);
}

std::string CompositeTransformation::transform(const std::string& text) const
{
	std::string transformedText = text;
	for (size_t i = 0; i < this->transformations.size(); i++)
	{
		transformedText = this->transformations[i]->transform(transformedText);
	}
	return transformedText;
}

bool CompositeTransformation::operator == (const TextTransformation& other) const
{
	const CompositeTransformation* castedOther = dynamic_cast<const CompositeTransformation*>(&other);
	if (castedOther)
	{
		if (this->transformations.size() != castedOther->transformations.size())
			return false;
		for (size_t i = 0; i < this->transformations.size(); i++)
		{
			if (!this->transformations[i]->operator==(*castedOther->transformations[i].get()))
				return false;
		}
		return true;
	}
	return false;
}

std::string CompositeTransformation::toString() const
{
	std::string toReturn = "Composite[ ";
	for (size_t i = 0; i < this->transformations.size(); i++)
	{
		toReturn += this->transformations[i]->toString();
		if (i!=this->transformations.size()-1)
		{
			toReturn += ", ";
		}
	}
	toReturn += " ]";
	return toReturn;
}

std::unique_ptr<TextTransformation> CompositeTransformation::clone() const
{
	std::vector<std::unique_ptr<TextTransformation>> copiedTransformations;
	for (size_t i = 0; i < this->transformations.size(); i++)
	{
		copiedTransformations.push_back(std::move(this->transformations[i]->clone()));
	}
	return std::make_unique<CompositeTransformation>(std::move(copiedTransformations));
}