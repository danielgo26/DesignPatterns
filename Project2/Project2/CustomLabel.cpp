#include "CustomLabel.h"
#include <string>
#include "CommonFunctionalities.h"

void CustomLabel::getLabelTextFromUser() const
{
	if (&this->readFrom == &std::cin)
		std::cout << "Enter label text: ";
	std::string value;
	std::getline(this->readFrom, value);
	setStringByDefaultIfEmpty(value);

	this->label = std::make_unique<SimpleLabel>(value);
}

void CustomLabel::getTimeoutResponseFromUser() const
{
	bool isFirstEntrance = true;
	while (true)
	{
		if (&this->readFrom == &std::cin) {
			std::cout << "Want to change the custom label's text?(y/n): ";
			if (isFirstEntrance)
				std::cin.ignore();
		}
		std::string response;
		std::getline(this->readFrom, response);
		if (response == "y")
		{
			getLabelTextFromUser();
			break;
		}
		else if (response == "n")
		{
			break;
		}
		else
		{
			system("cls");
			std::cout << "Wrong command! Enter \'y\' for \'yes\' or \'n\' for \'no\'! ";
		}
		isFirstEntrance = false;
	}
}

const std::unique_ptr<LabelImplementation>& CustomLabel::getLabel() const
{
	if (!this->label)
	{
		if (&this->readFrom == &std::cin)
			std::cin.ignore();
		getLabelTextFromUser();
	}
	else if (this->currTimeout == this->maxTimeout + 1)
	{
		getTimeoutResponseFromUser();
		this->currTimeout = 1;
	}
	return this->label;
}

//The constructor will validate the timeout to be only a positive number
CustomLabel::CustomLabel(std::istream& is, size_t timeout)
	:readFrom(is)
{
	if (timeout == 0) {
		timeout = 1;
		std::cout << "The timeout could not be 0! Timeout set to 1!" << std::endl;
	}
	this->maxTimeout = timeout;
}

//AFTER each maxTimeout callings of that function the user will be asked if the label text to be changed
std::string CustomLabel::getText() const
{
	this->currTimeout++;
	return std::move(getLabel()->getText());
}

bool CustomLabel::operator==(const LabelImplementation& other) const
{
	return getLabel()->operator==(other);
}

std::string CustomLabel::toString() const
{
	return "Custom text";
}