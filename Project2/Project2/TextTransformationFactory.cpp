#include "TextTransformationFactory.h"
#include "iostream"
#include "CapitalizeTransformation.h"
#include "LeftTrimTransformation.h"
#include "RightTrimTransformation.h"
#include "NormalizeSpaceTransformation.h"
#include "DecorateTransformation.h"
#include "CenzoreTransformation.h"
#include "ReplaceTransformation.h"
#include "CompositeTransformation.h"
#include "AppManager.h"
#include "CommonFunctionalities.h"
#include "CommonFunctionalities.h"
#include "MenuDisplay.h"
#include "TextTransformationContainer.h"
#include "ClassConstInvariants.h"
#include "CenzoreTransformationFactory.h"
#include "EnumMenuOptions.h"

using namespace std;

shared_ptr<TextTransformation> TextTransformationFactory::create()
{
	int trIndex;
	while (true)
	{
		printAvailableTextTransformationsMenu();
		std::string textTrIndex;
		cin >> textTrIndex;

		system("cls");
		if (!isIntegerFromRange(textTrIndex, trIndex, startTextTransformationTypeIndex, endTextTransformationTypeIndex))
		{
			cout << "Index should be a number in range( " << startTextTransformationTypeIndex << " - " << endTextTransformationTypeIndex << " )!" << endl;
			continue;
		}
		break;
	}
	if (trIndex == (int)textTransformations::capitalize)
	{
		system("cls");
		cout << "Successfully created!" << endl;
		return make_shared<CapitalizeTransformation>();
	}
	else if (trIndex == (int)textTransformations::leftTrim)
	{
		system("cls");
		cout << "Successfully created!" << endl;
		return make_shared<LeftTrimTransformation>();
	}
	else if (trIndex == (int)textTransformations::rightTrim)
	{
		system("cls");
		cout << "Successfully created!" << endl;
		return make_shared<RightTrimTransformation>();
	}
	else if (trIndex == (int)textTransformations::normalizeSpace)
	{
		system("cls");
		cout << "Successfully created!" << endl;
		return make_shared<NormalizeSpaceTransformation>();
	}
	else if (trIndex == (int)textTransformations::decorate)
	{
		system("cls");
		cout << "Successfully created!" << endl;
		return make_shared<DecorateTransformation>();
	}
	else if (trIndex == (int)textTransformations::cenzor)
	{
		string toCenzor;
		cout << "Enter the string to be cenzored: ";
		cin.ignore();
		getline(std::cin, toCenzor);

		system("cls");
		if (setStringByDefaultIfEmpty(toCenzor))
			cout << "Successfully created!" << endl;
	
		return CenzoreTransformationFactory::getCenzoreTransformation(toCenzor);
	}
	else if (trIndex == (int)textTransformations::replace)
	{
		string toBeReplaced, replaceWith;
		cin.ignore();
		cout << "Enter the string to be replaced: ";
		getline(std::cin, toBeReplaced);
		setStringByDefaultIfEmpty(toBeReplaced);

		cout << "Enter the string to replace with: ";
		getline(std::cin, replaceWith);

		system("cls");

		cout << "Successfully created!" << endl;
		return make_shared<ReplaceTransformation>(toBeReplaced, replaceWith);
	}
	else if (trIndex == (int)textTransformations::composite)
	{
		if (TextTransformationContainer::size() == 0)
		{
			cout << "No available text transformations!" << endl;
			return nullptr;
		}
		int countNumber;
		while (true)
		{
			cout << "Enter count of transformations to include: ";
			std::string input;
			cin >> input;
			system("cls");
			isIntegerFromRange(input, countNumber, 1, INT32_MAX);
			if (countNumber <= 0)
			{
				cout << "Enter valid index! " << endl;
				continue;
			}
			break;
		}

		vector<unique_ptr<TextTransformation>> transformations;
		for (size_t i = 0; i < countNumber; i++)
		{
			cout << "All available transformations:" << endl;
			AppManager::listAllTextTransformations();
			int numberIndex;
			while (true)
			{
				cout << "Choose transformation index: ";
				string inputIndex;
				cin >> inputIndex;
				system("cls");
				if (!isIntegerFromRange(inputIndex, numberIndex, 1, TextTransformationContainer::size()))
				{
					cout << "Enter valid index!" << endl;
					continue;
				}
				cout << "Successfully chosen!" << endl;
				break;
			}
			transformations.push_back(std::move(TextTransformationContainer::getTransformationByIndex(numberIndex - 1)->clone()));
		}
		cout << "Successfully created!" << endl;
		return make_shared<CompositeTransformation>(std::move(transformations));
	}
	return nullptr;
}