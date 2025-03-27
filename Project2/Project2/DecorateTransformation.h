#pragma once
#include "TextTransformation.h"

/// <summary>
/// Concrete transformation for text decorating
/// </summary>

class DecorateTransformation : public TextTransformation
{
public:
	std::string transform(const std::string& text) const override;
	bool operator==(const TextTransformation& other) const override;
	std::string toString() const override;
	std::unique_ptr<TextTransformation> clone() const override;
};