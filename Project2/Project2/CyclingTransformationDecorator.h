#pragma once
#include "TextTransformation.h"
#include "LabelDecoratorBase.h"
#include <vector>

/// <summary>
/// Concrete label decorator
/// Storing a list of transformation in order to apply a sequently chosen one on its underlying label
/// when getText() function is called
/// The class valid states demands neigher of its transformations not to be nullptr
/// Throws in the constructor if any of the given transformations is invalid(nullptr)
/// The start transformation index of the sequence is set to zero in the constructor by default
/// The current transformation index of the sequence is in mutable state in order to 
/// both reach the const criteria of the getText() function and update the next transformaiton to be applied
/// </summary>

class CyclingTransformationDecorator : public LabelDecoratorBase
{
private:
	mutable size_t indexOfTransformationToBeApplied;
	std::vector<std::unique_ptr<TextTransformation>> transformationsList;
protected:
	std::unique_ptr<Label> getLabelWithoutDecorator(const Label& decorator) override;
public:
	CyclingTransformationDecorator(std::unique_ptr<Label> label,
		std::vector<std::unique_ptr<TextTransformation>> transformationsList, size_t startTransformationIndex = 0);
	std::string getText() const override;
	bool operator==(const Label& other) const override;
	std::string toString() const override;
};