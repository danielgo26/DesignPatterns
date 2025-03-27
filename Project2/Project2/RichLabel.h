#pragma once
#include "Label.h"

/// <summary>
/// Concrete label implementation
/// Corresponding selectors and mutators included
/// </summary>

class RichLabel :public LabelImplementation
{
private:
	std::string value;
	std::string color;
	std::string fontName;
	double fontSize;
public:
	RichLabel(std::string value, std::string color, std::string fontName, double fontSize);

	const std::string& getColor() const;
	const std::string& getFontName() const;
	double getFontSize() const;

	void setColor(const std::string& color);
	void setFontName(const std::string& fontName);
	void setFontSize(double size);

	std::string getText() const override;
	bool operator==(const LabelImplementation& other) const override;
	std::string toString() const override;

	
};