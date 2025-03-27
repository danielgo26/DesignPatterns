#pragma once
#include "TextTransformation.h"

/// <summary>
/// Concrete transformation for removing intervals in the end of the string
/// </summary>

class RightTrimTransformation : public TextTransformation
{
public:
	std::string transform(const std::string& text) const override;
	bool operator==(const TextTransformation& other) const override;
	std::string toString() const override;
	std::unique_ptr<TextTransformation> clone() const override;
};