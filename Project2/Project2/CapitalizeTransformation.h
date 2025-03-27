#pragma once
#include "TextTransformation.h"

/// <summary>
/// Concrete transformation for text capitalizing
/// </summary>

class CapitalizeTransformation : public TextTransformation
{
public:
	std::string transform(const std::string& text) const override;
	virtual bool operator==(const TextTransformation& other) const override;
	std::string toString() const override;
	std::unique_ptr<TextTransformation> clone() const override;
};