#pragma once
#include "Label.h"

/// <summary>
/// Class for label with help text
/// </summary>

class HelpLabel : public Label
{
private:
	std::string helpText;
public:
	HelpLabel(std::unique_ptr<LabelImplementation> label, std::string helpText);
	const std::string& getHelpText() const;
	void setHelpText(const std::string& helpText);

	std::string getText() const override;
	bool operator==(const Label& other) const override;
	std::string toString() const override;
};
