#include "LabelFactory.h"
#include <string>
#include "HelpLabel.h"
#include "CommonFunctionalities.h"
#include "MenuDisplay.h"
#include "AppManager.h"
#include "TextTransformationDecorator.h"
#include "RandomTransformationDecorator.h"
#include "CyclingTransformationDecorator.h"
#include "LabelContainer.h"
#include "TextTransformationContainer.h"
#include "ClassConstInvariants.h"
#include "EnumMenuOptions.h"

using namespace std;

std::unique_ptr<Label> LabelFactory::create(std::unique_ptr<LabelImplementation> impl)
{
	if (!impl)
		throw std::invalid_argument("Invalid label implementation!");
	int optionIndex;
	while (true)
	{
		printAvailableLabelsMenu();
		std::string labelOptionIndex;
		cin >> labelOptionIndex;
		system("cls");
		if (!isIntegerFromRange(labelOptionIndex, optionIndex, startHelpOptionIndexCreate, endHelpOptionIndexCreate))
		{
			cout << "Index should be a number in range( " << startHelpOptionIndexCreate << " - " << endHelpOptionIndexCreate << " )!" << endl;
			continue;
		}
		break;
	}
	if (optionIndex == (int)labels::withHelp)
	{
		string helpText;
		cout << "Enter help text: ";
		cin.ignore();
		getline(std::cin, helpText);
		system("cls");

		if (setStringByDefaultIfEmpty(helpText))
			cout << "Label successfully created!" << endl;

		return make_unique<HelpLabel>(std::move(impl), helpText);
	}
	else if (optionIndex == (int)labels::withoutHelp)
	{
		system("cls");
		cout << "Label successfully created!" << endl;
		return make_unique<Label>(std::move(impl));
	}
	return nullptr;
}

void LabelFactory::decorate(std::unique_ptr<Label> toDecorate)
{
	if (!toDecorate)
		throw std::invalid_argument("Invalid label to decorate!");
	//get the type of decoration
	int decorationIndex;
	while (true)
	{
		cout << "----Decorations----" << endl;
		printAvailableDecorations();
		string decoration;
		cin >> decoration;
		system("cls");
		if (!isIntegerFromRange(decoration, decorationIndex, startTypeDecorationIndex, endTypeDecorationIndex))
		{
			cout << "Enter a valid index!" << endl;
			continue;
		}
		break;
	}

	//get needed transformations for that decoration
	if (TextTransformationContainer::size() == 0)
	{
		cout << "No transformations available(create some first)!" << endl;
		LabelContainer::addLabel(std::move(toDecorate));
		return;
	}

	int countTr;
	//text transformation depends only on one transformation
	if (decorationIndex == (int)decorators::textTransformation)
		countTr = 1;
	else
	{
		while (true)
		{
			cout << "Enter count of transformations to include: ";
			std::string inputCount;
			cin >> inputCount;
			isIntegerFromRange(inputCount, countTr, 1, INT32_MAX);
			if (countTr <= 0)
			{
				cout << "Enter a positive number for count! " << endl;
				continue;
			}
			break;
		}
	}
	vector<unique_ptr<TextTransformation>> transformations;
	for (size_t i = 0; i < countTr; i++)
	{
		cout << "All available transformations:" << endl;
		AppManager::listAllTextTransformations();
		int numberIndex;
		while (true)
		{
			cout << "Choose transformation index: ";
			string inputIndex;
			cin >> inputIndex;
			if (!isIntegerFromRange(inputIndex, numberIndex, 1, TextTransformationContainer::size()))
			{
				cout << "Enter valid index!" << endl;
				continue;
			}
			break;
		}
		transformations.push_back(std::move(TextTransformationContainer::getTransformationByIndex(numberIndex - 1)->clone()));
	}

	//decorate
	if (decorationIndex == (int)decorators::textTransformation)
	{
		toDecorate =
			std::move(make_unique<TextTransformationDecorator>(std::move(toDecorate), std::move(transformations[0])));
	}
	else if (decorationIndex == (int)decorators::randomTransformation)
	{
		toDecorate =
			std::move(make_unique<RandomTransformationDecorator>(std::move(toDecorate), std::move(transformations)));
	}
	else if (decorationIndex == (int)decorators::cyclingTransformation)
	{
		toDecorate =
			std::move(make_unique<CyclingTransformationDecorator>(std::move(toDecorate), std::move(transformations)));
	}

	LabelContainer::addLabel(std::move(toDecorate));

	system("cls");
	cout << "Successfully decorated!" << endl;
}