#pragma once
#include <iostream>
#include "ClassConstInvariants.h"

using namespace std;

namespace {
	void printMainMenu()
	{
		cout << endl;
		cout << "----Main menu----" << endl;
		cout << "1. Create Label" << endl;
		cout << "2. Create Text Transformation" << endl;
		cout << "3. Decorate Label" << endl;
		cout << "4. List all labels" << endl;
		cout << "5. List all text transformations" << endl;
		cout << "6. Delete label" << endl;
		cout << "7. Delete text transformation" << endl;
		cout << "8. Remove decorator" << endl;
		cout << "9. Get label text" << endl;
		cout << "10. Exit" << endl;

		cout << "Choose index of operation: ";
	}

	void printAvailableLabelImplementationsMenu()
	{
		cout << "----Available label types----" << endl;
		cout << "-----------------------------" << endl;
		cout << "1. Simple label" << endl;
		cout << "2. Rich label" << endl;
		cout << "3. Custom label" << endl;
		cout << "-----------------------------" << endl;

		cout << "Select the type of label to be created: ";
	}

	void printAvailableLabelsMenu()
	{
		cout << "----Available label options----" << endl;
		cout << "-------------------------------" << endl;
		cout << "1. With help text" << endl;
		cout << "2. Without help text" << endl;
		cout << "-------------------------------" << endl;

		cout << "Select the type of option to be added: ";
	}

	void printAvailableTextTransformationsMenu()
	{
		cout << "----Text transformations----" << endl;
		cout << "1. Capitalize" << endl;
		cout << "2. Left trim" << endl;
		cout << "3. Right trim" << endl;
		cout << "4. Normalize space" << endl;
		cout << "5. Decorate" << endl;
		cout << "6. Cenzor" << endl;
		cout << "7. Replace" << endl;
		cout << "8. Composite" << endl;

		cout << "Choose operation index: ";
	}

	void printAvailableDecorations()
	{
		cout << "1. Text Transformation" << endl;
		cout << "2. Random Transformation" << endl;
		cout << "3. Cycling Transformation" << endl;

		cout << "Choose decoration index: ";
	}
}