#include <iostream>
#include "MenuDisplay.h"
#include "CommonFunctionalities.h"
#include "AppManager.h"
#include "EnumMenuOptions.h"

using namespace std;

int main()
{	
	while (true)
	{
		printMainMenu();
		string operationIndex;
		cin >> operationIndex;
		int index;

		if (!isIntegerFromRange(operationIndex, index, startOptionIndexMainMenu, endOptionIndexMainMenu))
		{
			system("cls");
			cout << "Index should be a number in range( " << startOptionIndexMainMenu << " - " << endOptionIndexMainMenu << " )!" << endl;
			continue;
		}
		switch (index)
		{
		case (int)mainMenuOptions::CreateLabel:
			system("cls");
			AppManager::createLabel();
			break;
		case (int)mainMenuOptions::CreateTextTransformation:
			system("cls");
			AppManager::createTextTransformation();
			break;
		case (int)mainMenuOptions::DecorateLabel:
			system("cls");
			AppManager::decorateLabel();
			break;
		case (int)mainMenuOptions::ListAllLabels:
			system("cls");
			AppManager::listAllLabels();
			break;
		case (int)mainMenuOptions::ListAllTextTransformations:
			system("cls");
			AppManager::listAllTextTransformations();
			break;
		case (int)mainMenuOptions::DeleteLabel:
			system("cls");
			AppManager::deleteLabel();
			break;
		case (int)mainMenuOptions::DeleteTextTransformation:
			system("cls");
			AppManager::deleteTransformation();
			break;
		case (int)mainMenuOptions::RemoveDecorator:
			system("cls");
			AppManager::removeDecorator();
			break;
		case (int)mainMenuOptions::GetLabelContent:
			system("cls");
			AppManager::getContent();
			break;
		case (int)mainMenuOptions::Exit:
			return 0;
		default:
			break;
		}
	}
}
