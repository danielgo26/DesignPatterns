#include "TextTransformationContainer.h"

std::vector <std::shared_ptr<TextTransformation>> TextTransformationContainer::transformations =
std::vector<std::shared_ptr<TextTransformation>>();

int TextTransformationContainer::size()
{
	return transformations.size();
}

void TextTransformationContainer::addTransformation(std::shared_ptr<TextTransformation> toAdd)
{
	if (toAdd)
		transformations.push_back(std::move(toAdd));
}

void TextTransformationContainer::removeTransformationAtIndex(size_t index)
{
	if (index <= transformations.size())
		transformations.erase(transformations.begin() + index);
}

const std::shared_ptr<TextTransformation>& TextTransformationContainer::getTransformationByIndex(size_t index)
{
	if (index <= transformations.size())
		return transformations[index];
	return nullptr;
}