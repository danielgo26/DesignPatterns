#pragma once
#include "SimpleLabel.h"
#include <iostream>

/// <summary>
/// Concrete label implementation
/// Custom label's text is set on its first demand from the user
/// After timeout label's text demanding from the user, a option for text change is reached
/// (For example for timeout set to three, on the forth text demanding the text change option is displayed)
/// By default the stream for user interaction is the standart input std::cin and the timeout count is set to 3
/// </summary>

class CustomLabel : public LabelImplementation
{
private:
	std::istream& readFrom;
	size_t maxTimeout;
	mutable size_t currTimeout = 0;
	mutable std::unique_ptr<LabelImplementation> label = nullptr;
	const std::unique_ptr<LabelImplementation>& getLabel() const;
	void getLabelTextFromUser() const;
	void getTimeoutResponseFromUser() const;
public:
	CustomLabel(std::istream& is = std::cin, size_t timeout = 3);
	std::string getText() const override;
	bool operator==(const LabelImplementation& other) const override;
	std::string toString() const override;
};