#include <iostream>
#include "AppManager.h"
#include "PrintManager.h"
#include "LabelContainer.h"
#include "TextTransformationContainer.h"
#include "LabelFactory.h"
#include "LabelImplementationFactory.h"
#include "TextTransformationFactory.h"
#include "CommonFunctionalities.h"
#include "MenuDisplay.h"
#include "TextTransformationDecorator.h"
#include "RandomTransformationDecorator.h"
#include "CyclingTransformationDecorator.h"
#include "ClassConstInvariants.h"
#include "EnumMenuOptions.h"

void AppManager::createLabel()
{
	LabelContainer::addLabel(std::move(LabelFactory::create(LabelImplementationFactory::create())));
}

void AppManager::createTextTransformation()
{
	std::shared_ptr<TextTransformation> tr = std::move(TextTransformationFactory::create());
	if (tr.get())
		TextTransformationContainer::addTransformation(std::move(tr));
}

void AppManager::decorateLabel()
{
	//choose label	
	int indexLabel;
	while (true)
	{
		if (LabelContainer::size() == 0)
		{
			cout << "No labels to decorate!" << endl;
			return;
		}
		AppManager::listAllLabels();
		cout << "Choose label index to decorate: ";
		string labelToDecorate;
		cin >> labelToDecorate;
		system("cls");
		if (!isIntegerFromRange(labelToDecorate, indexLabel, 1, LabelContainer::size()))
		{
			cout << "Enter a valid index!" << endl;
			continue;
		}
		cout << "Successfully selected!" << endl;
		break;
	}
	//decorate
	LabelFactory::decorate(std::move(LabelContainer::removeLabelAtIndex(indexLabel - 1)));
}

void AppManager::listAllLabels()
{
	cout << "----Labels----" << endl;
	if (LabelContainer::size() == 0)
	{
		cout << "No labels to show!" << endl;
		return;
	}
	for (size_t i = 0; i < LabelContainer::size(); i++)
	{
		cout << i + 1 << ". " << LabelContainer::getLabelByIndex(i)->toString() << endl;
	}
}

void AppManager::listAllTextTransformations()
{
	cout << "----Text transformations----" << endl;
	if (TextTransformationContainer::size() == 0)
	{
		cout << "No text transformations to show!" << endl;
		return;
	}
	for (size_t i = 0; i < TextTransformationContainer::size(); i++)
	{
		cout << i + 1 << ". " << TextTransformationContainer::getTransformationByIndex(i)->toString() << endl;
	}
}

void AppManager::deleteLabel()
{
	if (LabelContainer::size() == 0)
	{
		cout << "No labels to delete" << endl;
		return;
	}
	int indexLabel;
	while (true)
	{
		listAllLabels();
		cout << "Choose index label to remove: ";
		string indexChosen;
		cin >> indexChosen;
		system("cls");
		if (!isIntegerFromRange(indexChosen, indexLabel, 1, LabelContainer::size()))
		{
			cout << "Enter a valid index!" << endl;
			continue;
		}
		break;
	}
	LabelContainer::removeLabelAtIndex(indexLabel - 1);
	cout << "Successfully deleted!" << endl;
}

void AppManager::deleteTransformation()
{
	if (TextTransformationContainer::size() == 0)
	{
		cout << "No transformations to delete" << endl;
		return;
	}
	int indexTr;
	while (true)
	{
		listAllTextTransformations();
		cout << "Choose index transformation to be deleted: ";
		string chosenIndex;
		cin >> chosenIndex;
		system("cls");
		if (!isIntegerFromRange(chosenIndex, indexTr, 1, TextTransformationContainer::size()))
		{
			cout << "Enter valid index!" << endl;
			continue;
		}
		break;
	}
	TextTransformationContainer::removeTransformationAtIndex(indexTr - 1);
	cout << "Successfully deleted!" << endl;
}

void AppManager::removeDecorator()
{
	//get label to remove decorator from 
	if (LabelContainer::size() == 0)
	{
		cout << "No labels available!" << endl;
		return;
	}
	int indexDecorator;
	while (true)
	{
		listAllLabels();
		cout << "Enter index of label to remove decorator from: ";
		string decIndex;
		cin >> decIndex;
		system("cls");
		if (!isIntegerFromRange(decIndex, indexDecorator, 1, LabelContainer::size()))
		{
			cout << "Enter a valid index!" << endl;
			continue;
		}
		cout << "Successfully chosen!" << endl;
		break;
	}

	//get type of decorator to remove
	int decTypeIndex;
	while (true)
	{
		printAvailableDecorations();
		string typeInput;
		cin >> typeInput;
		system("cls");
		if (!isIntegerFromRange(typeInput, decTypeIndex, startTypeDecorationIndex, endTypeDecorationIndex))
		{
			cout << "Enter a valid index!" << endl;
			continue;
		}
		cout << "Successfully chosen!" << endl;
		break;
	}

	//get transformation list
	if (TextTransformationContainer::size() == 0)
	{
		cout << "No transformations available(create some first)!" << endl;
		return;
	}

	int countTr;
	if (decTypeIndex == 1)//text transformation depands only one transformation
		countTr = 1;
	else
	{
		while (true)
		{
			cout << "Enter count of transformations to include: ";
			std::string inputCount;
			cin >> inputCount;
			system("cls");
			isIntegerFromRange(inputCount, countTr, 1, INT32_MAX);
			if (countTr <= 0)
			{
				cout << "Enter valid index! " << endl;
				continue;
			}
			break;
		}
	}
	vector<unique_ptr<TextTransformation>> transformations;
	for (size_t i = 0; i < countTr; i++)
	{
		cout << "All available transformations:" << endl;
		listAllTextTransformations();
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
			break;
		}
		transformations.push_back(std::move(TextTransformationContainer::getTransformationByIndex(numberIndex - 1)->clone()));
	}

	//remove
	std::unique_ptr<Label> removed;
	if (decTypeIndex == (int)decorators::textTransformation)
	{
		removed = std::move(
			LabelDecoratorBase::removeDecorator(
				std::move(LabelContainer::removeLabelAtIndex(indexDecorator - 1)),
				TextTransformationDecorator(nullptr, std::move(transformations[0]))
			)
		);
	}
	else if (decTypeIndex == (int)decorators::randomTransformation)
	{
		removed = std::move(
			LabelDecoratorBase::removeDecorator(
				std::move(LabelContainer::removeLabelAtIndex(indexDecorator - 1)),
				RandomTransformationDecorator(nullptr, std::move(transformations))
			)
		);
	}
	else if (decTypeIndex == (int)decorators::cyclingTransformation)
	{
		removed = std::move(
			LabelDecoratorBase::removeDecorator(
				std::move(LabelContainer::removeLabelAtIndex(indexDecorator - 1)),
				CyclingTransformationDecorator(nullptr, std::move(transformations))
			)
		);
	}
	LabelContainer::addLabel(std::move(removed));
	system("cls");
	cout << "Operation executed successfully!" << endl;
}

void AppManager::getContent()
{
	if (LabelContainer::size() == 0)
	{
		cout << "No labels available" << endl;
		return;
	}
	//get label
	int labelIndex;
	while (true)
	{
		AppManager::listAllLabels();
		cout << "Choose label index: ";
		string labelIndexInput;
		cin >> labelIndexInput;
		system("cls");
		if (!isIntegerFromRange(labelIndexInput, labelIndex, 1, LabelContainer::size()))
		{
			cout << "Enter valid index!" << endl;
			continue;
		}
		cout << "Successfully chosen!" << endl;
		break;
	}

	//choose option
	int optionIndex;
	while (true)
	{
		printAvailableLabelsMenu();
		string optionInput;
		cin >> optionInput;
		system("cls");
		if (!isIntegerFromRange(optionInput, optionIndex, startHelpOptionIndexCreate, endHelpOptionIndexCreate))
		{
			cout << "Enter valid index!" << endl;
			continue;
		}
		break;
	}

	//print
	switch (optionIndex)
	{
	case (int)labels::withHelp:
		PrintManager::printWithHelpText(*LabelContainer::getLabelByIndex(labelIndex - 1));
		break;
	case (int)labels::withoutHelp:
		PrintManager::print(*LabelContainer::getLabelByIndex(labelIndex - 1));
		break;
	default:
		break;
	}
}