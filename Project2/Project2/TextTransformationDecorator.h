#pragma once
#include "TextTransformation.h"
#include "LabelDecoratorBase.h"

/// <summary>
/// Concrete label decorator
/// Storing only one transformation in order to apply it on its underlying label when getText() function is called
/// The class valid state demands its transformation not to be nullptr
/// Throws in the constructor if invalid(nullptr) transformation is given
/// The random seed is set in the class constructor
/// </summary>

class TextTransformationDecorator : public LabelDecoratorBase
{
private:
	std::unique_ptr<TextTransformation> transformation;
protected:
	std::unique_ptr<Label> getLabelWithoutDecorator(const Label& decorator) override;
public:
	TextTransformationDecorator(std::unique_ptr<Label> label, std::unique_ptr<TextTransformation> transformation);
	std::string getText() const override;
	bool operator==(const Label& other) const override;
	std::string toString() const override;
};