#pragma once
#include "Label.h"

/// <summary>
/// Base class for label decorators
/// This class can store nullptr for its decorated label property in order to make the usage of the removeDecorator()
/// function more efficient in aspect of dynamic memory alocation
/// Save for derefering a nullptr value in its properties
/// Throws if trying to remove a decorator from a nullptr value 
/// </summary>

class LabelDecoratorBase :public Label
{
protected:
	std::unique_ptr<Label> label;
	virtual std::unique_ptr<Label> getLabelWithoutDecorator(const Label& decorator);
public:
	LabelDecoratorBase(std::unique_ptr<Label> label);
	std::string getText() const override;
	const std::unique_ptr<Label>& getLabel() const;
	static std::unique_ptr<Label> removeDecorator(std::unique_ptr<Label> label,
		const Label& decorator);
	bool operator==(const Label& other) const override;
	std::string toString() const override;
};