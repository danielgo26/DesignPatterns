#pragma once
#include "TextTransformation.h"

/// <summary>
/// Concrete transformation for text substring replacement
/// The substring to replace and the string to replace with are set in the constructors
/// Selectors and mutators involved
/// </summary>

class ReplaceTransformation : public TextTransformation
{
private:
	std::string stringToBeReplaced;
	std::string stringToReplaceWith;
public:
	ReplaceTransformation(std::string stringToBeReplaced, std::string stringToReplaceWith);

	const std::string& getStringToBeReplaced() const;
	const std::string& getStringToReplaceWith() const;

	void setStringToBeReplaced(const std::string& stringToBeReplaced);
	void setStringToReplaceWith(const std::string& stringToReplaceWith);

	std::string transform(const std::string& text) const override;
	virtual bool operator==(const TextTransformation& other) const override;
	std::string toString() const override;
	std::unique_ptr<TextTransformation> clone() const override;
};
