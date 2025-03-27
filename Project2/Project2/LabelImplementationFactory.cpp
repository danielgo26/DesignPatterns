#include <string>
#include <limits>
#include "LabelImplementationFactory.h"
#include "SimpleLabel.h"
#include "RichLabel.h"
#include "CustomLabel.h"
#include "CommonFunctionalities.h"
#include "MenuDisplay.h"
#include "ClassConstInvariants.h"
#include "EnumMenuOptions.h"

using namespace std;

unique_ptr<LabelImplementation> LabelImplementationFactory::create()
{
	int typeLabelIndex;
	while (true)
	{
		printAvailableLabelImplementationsMenu();
		std::string labelTypeIndex;
		cin >> labelTypeIndex;
		system("cls");
		if (!isIntegerFromRange(labelTypeIndex, typeLabelIndex, startTypeOfLabelOptionIndex, endTypeOfLabelOptionIndex))
		{
			cout << "Index should be a number in range( " << startTypeOfLabelOptionIndex << " - " << endTypeOfLabelOptionIndex << " )!" << endl;
			continue;
		}
		break;
	}
	if (typeLabelIndex == (int)labelImplementations::simpleLabel)
	{
		string content;
		cout << "Enter lable's content: ";
		cin.ignore();
		getline(std::cin, content);

		system("cls");
		if (setStringByDefaultIfEmpty(content))
			cout << "Implementation successfully created!" << endl;
		return make_unique<SimpleLabel>(content);
	}
	else if (typeLabelIndex == (int)labelImplementations::richLabel)
	{
		string content, color, fontName, fontSizeString;
		double fontSize;
		cout << "Enter lable's content: ";
		cin.ignore();
		getline(std::cin, content);
		setStringByDefaultIfEmpty(content);

		cout << "Enter lable's color: ";
		getline(std::cin, color);
		setStringByDefaultIfEmpty(color);

		cout << "Enter lable's font-name: ";
		getline(std::cin, fontName);
		setStringByDefaultIfEmpty(fontName);

		while (true)
		{
			cout << "Enter lable's font-size: ";
			getline(std::cin, fontSizeString);
			if (!isDoubleFromRange(fontSizeString, fontSize, 0.1, std::numeric_limits<double>::max()))
			{
				cout << "Enter a valid float value!" << endl;
				continue;
			}
			break;
		}
		system("cls");
		cout << "Implementation successfully created!" << endl;
		return make_unique <RichLabel>(content, color, fontName, fontSize);
	}
	else if (typeLabelIndex == (int)labelImplementations::customLabel)
	{
		cout << "Implementation successfully created!" << endl;
		return make_unique<CustomLabel>();
	}
	return nullptr;
}