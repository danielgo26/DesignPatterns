#pragma once
#include "TextTransformation.h"

/// <summary>
/// Concrete transformation for text cenzoring
/// The text to be cenzored and the cenzore pattern are set in the constructor
/// The cenzore pattern by default is '*'
/// No mutators involved in order to achieve an immutable state of objects for the flyweight pattern
/// </summary>

class CenzoreTransformation : public TextTransformation
{
private:
	char cenzorWith;
	std::string stringToCenzor;
public:
	CenzoreTransformation(std::string stringToCenzor, char cenzorWith = '*');
	const std::string& getStringToCenzor() const;

	std::string transform(const std::string& text) const override;
	virtual bool operator==(const TextTransformation& other) const override;
	std::string toString() const override;
	std::unique_ptr<TextTransformation> clone() const override;
};
