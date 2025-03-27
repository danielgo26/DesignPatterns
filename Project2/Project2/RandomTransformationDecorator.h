#pragma once
#include <vector>
#include <memory>
#include <random>
#include "TextTransformation.h"
#include "LabelDecoratorBase.h"

/// <summary>
/// Concrete label decorator
/// Storing a list of transformation in order to apply a randomly chosen one on its underlying label
/// when getText() function is called
/// The class valid states demands neigher of its transformations not to be nullptr
/// Throws in the constructor if any of the given transformations is invalid(nullptr)
/// </summary>

class RandomTransformationDecorator : public LabelDecoratorBase
{
private:
	std::random_device rd;
	mutable std::mt19937 gen;
	std::vector<std::unique_ptr<TextTransformation>> transformationsList;
protected:
	std::unique_ptr<Label> getLabelWithoutDecorator(const Label& decorator) override;
public:
	RandomTransformationDecorator(std::unique_ptr<Label> label,
		std::vector<std::unique_ptr<TextTransformation>> transformationsList);
	std::string getText() const override;
	bool operator==(const Label& other) const override;
	std::string toString() const override;
};