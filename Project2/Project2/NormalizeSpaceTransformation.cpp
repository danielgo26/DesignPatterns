#include "NormalizeSpaceTransformation.h"

std::string NormalizeSpaceTransformation::transform(const std::string& text) const
{
	bool lastCharWasSpace = false;
	std::string normalized;

	int indexReadTo = text.size();
	if (text[text.size() - 1] == ' ')
	{
		indexReadTo--;
		while (indexReadTo >= 0 && text[indexReadTo] == ' ')
		{
			indexReadTo--;
		}
		indexReadTo++;
	}
	bool isLeadingInterval = true;
	int currentIndex = 0;
	for (char ch : text) {
		if (currentIndex == indexReadTo)
		{
			for (size_t i = currentIndex; i < text.size(); i++)
			{
				normalized.push_back(' ');
			}
			break;
		}

		if (std::isspace(ch)) {
			if (isLeadingInterval)
			{
				normalized.push_back(' ');
			}
			else if (!lastCharWasSpace) {
				normalized.push_back(' ');
			}
			lastCharWasSpace = true;
		}
		else {
			isLeadingInterval = false;
			normalized.push_back(ch);
			lastCharWasSpace = false;
		}
		currentIndex++;
	}

	return normalized;
}

bool NormalizeSpaceTransformation::operator==(const TextTransformation& other) const
{
	return dynamic_cast<const NormalizeSpaceTransformation*>(&other);
}

std::string NormalizeSpaceTransformation::toString() const
{
	return "Normalize space";
}

std::unique_ptr<TextTransformation> NormalizeSpaceTransformation::clone() const
{
	return std::make_unique<NormalizeSpaceTransformation>();
}