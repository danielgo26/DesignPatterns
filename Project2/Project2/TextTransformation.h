#pragma once
#include <string>
#include <fstream>

/// <summary>
/// Base abstract class for text transformations
/// </summary>

class TextTransformation
{
public:
	virtual std::string transform(const std::string& text) const = 0;
	virtual bool operator==(const TextTransformation& other) const = 0;
	virtual std::string toString() const = 0;
	virtual std::unique_ptr<TextTransformation> clone() const = 0;

	virtual ~TextTransformation() = default;
};