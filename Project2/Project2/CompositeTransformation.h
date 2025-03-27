#pragma once
#include "TextTransformation.h"
#include <vector>

/// <summary>
/// Concrete transformation for applying multiple text transformaitons
/// The list of transformations is set in the constructor
/// The constructor throws if any of the given transformations is invalid(nullptr)
/// </summary>

class CompositeTransformation : public TextTransformation
{
private:
	std::vector<std::unique_ptr<TextTransformation>> transformations;
public:
	CompositeTransformation(std::vector<std::unique_ptr<TextTransformation>> transformations);
	std::string transform(const std::string& text) const override;
	bool operator==(const TextTransformation& other) const override;
	std::string toString() const override;
	std::unique_ptr<TextTransformation> clone() const override;
};