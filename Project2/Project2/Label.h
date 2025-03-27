#pragma once
#include <fstream>
#include "LabelImplementation.h"

/// <summary>
///	Base label class without help information, storing a concrete label implementation (bridge pattern used)
/// The valid state of that class does not hold a nullptr as composed label, so a validation is made in the constructor
/// and if so, it throws an invalid_argument exception 
/// </summary>

class Label
{
protected:
	std::unique_ptr<LabelImplementation> label = nullptr;
	Label() = default;
public:
	Label(std::unique_ptr<LabelImplementation> label);
	virtual std::string getText() const;
	virtual bool operator==(const Label& other) const;
	virtual std::string toString() const;
	virtual ~Label() = default;
};