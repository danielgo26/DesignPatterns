#pragma once
#include "Label.h"

/// <summary>
/// Concrete label implementation
/// </summary>

class SimpleLabel : public LabelImplementation
{
private:
	std::string value;
public:
	SimpleLabel(std::string value);
	bool operator==(const LabelImplementation& other) const override;
	std::string getText() const override;
	std::string toString() const override;
};