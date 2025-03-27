#include <iostream>
#include "AbstractFactory.h"
#include "Figure.h"
#include "FigureContainer.h"
#include <fstream>

std::unique_ptr<BaseFactory> getFactory()
{
	while (true)
	{
		std::cout << "Enter the way the figure will be created(random/stdin/file): ";
		std::string wayOfCreation;
		std::cin >> wayOfCreation;

		try
		{
			return AbstractFactory::create(wayOfCreation);
		}
		catch (const std::invalid_argument& e)
		{
			system("cls");
			std::cout << "Wrong input. " << e.what() << std::endl;
		}
	}
}

int getCountFiguresToGenerate()
{
	while (true)
	{
		std::cout << "Enter count of figures to be created: ";
		std::string countInput;
		std::cin >> countInput;
		std::cin.ignore();

		int count;
		try
		{
			count = std::stoi(countInput);
		}
		catch (const std::exception&)
		{
			system("cls");
			std::cout << "Count of figures is not a valid positive number!" << std::endl;
			continue;
		}
		if (count < 0)
		{
			system("cls");
			std::cout << "Wrong count of figures!" << std::endl;
			continue;
		}
		else
			return count;
	}
}

std::unique_ptr<Figure> getFigureFromFactory(std::unique_ptr<BaseFactory>& factory,
	bool& isFiguredCreated, bool& noFigureToRead)
{
	std::unique_ptr<Figure> figure;
	try
	{
		figure = factory->create();
		isFiguredCreated = true;
		noFigureToRead = false;
	}
	catch (const std::length_error& e)
	{
		system("cls");
		std::cout << "Unmatching count of figure's edges. " << e.what() << std::endl;
		isFiguredCreated = false;
		noFigureToRead = false;
	}
	catch (const std::invalid_argument& e)
	{
		system("cls");
		std::cout << "Invalid argument. " << e.what() << std::endl;
		isFiguredCreated = false;
		noFigureToRead = false;
	}
	catch (const std::logic_error& e)
	{
		system("cls");
		std::cout << "Logic error. " << e.what() << std::endl;
		isFiguredCreated = false;
		noFigureToRead = true;
	}
	catch (const std::exception& e)
	{
		system("cls");
		std::cout << "Error has occured. " << e.what() << std::endl;
		isFiguredCreated = false;
		noFigureToRead = false;
	}
	catch (...)
	{
		system("cls");
		std::cout << "Unknown error has occured." << std::endl;
		isFiguredCreated = false;
		noFigureToRead = false;
	}
	return figure;
}

bool fillContainerWithFiguresFromFactory(FigureContainer& container, std::unique_ptr<BaseFactory>& factory, int count)
{
	size_t i = 0;
	for (; i < count; i++)
	{
		bool isCreated = false;
		bool noFigureToRead = true;
		std::unique_ptr<Figure> figure = getFigureFromFactory(factory, isCreated, noFigureToRead);
		if (noFigureToRead)
		{
			std::cout << "Could read only " << i << " figures." << std::endl;
			return true;
		}
		if (!isCreated)
		{
			container.clear();
			return false;
		}
		container.moveToCollection(std::move(figure));
	}

	std::cout << "Figures generated successfully!" << std::endl;
	return true;
}

void printMainOperations()
{
	std::cout << "Choose an operation:" << std::endl;
	std::cout << "1. List all" << std::endl;
	std::cout << "2. Delete figure" << std::endl;
	std::cout << "3. Dublicate" << std::endl;
	std::cout << "4. Save to a file" << std::endl;
	std::cout << "5. Exit" << std::endl;
	std::cout << "Enter operation index: ";
}

bool getUserIndex(int& index, int from, int to)
{
	std::string indexInput;
	std::cin >> indexInput;
	try
	{
		index = std::stoi(indexInput);
	}
	catch (const std::exception&)
	{
		system("cls");
		std::cout << indexInput << " is not a number!" << std::endl;
		return false;
	}
	if (index < from || index > to)
	{
		system("cls");
		std::cout << indexInput << " is out of range(" << from << " - " << to << ")!" << std::endl;
		return false;
	}
	return true;
}

void printAllFigures(FigureContainer& container)
{
	std::cout << "Figures:" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	for (size_t i = 0; i < container.size(); i++)
	{
		std::cout << i << ". " << container[i].toString() << std::endl;
	}
	std::cout << "---------------------------------------" << std::endl;
}

void removeFigure(FigureContainer& container)
{
	if (container.size() == 0)
	{
		system("cls");
		std::cout << "No figures to remove!" << std::endl;
		return;
	}
	int index;
	while (true)
	{
		std::cout << "Choose index: ";
		if (getUserIndex(index, 0, container.size() - 1))
			break;
	}
	container.removeAt(index);
	system("cls");
	std::cout << "Successfully removed" << std::endl;
}

void dublicateFigure(FigureContainer& container)
{
	if (container.size() == 0)
	{
		system("cls");
		std::cout << "No figures to dublicate!" << std::endl;
		return;
	}
	int index;
	while (true)
	{
		std::cout << "Choose index: ";
		if (getUserIndex(index, 0, container.size() - 1))
			break;
	}
	container.moveToCollection(container[index].clone());
	system("cls");
	std::cout << "Successfully dublicated" << std::endl;
}

void saveToFile(FigureContainer& container)
{
	if (container.size() == 0)
	{
		system("cls");
		std::cout << "No figures to save!" << std::endl;
		return;
	}
	std::cout << "Enter name of file to save into: ";
	std::string fileName;
	std::cin >> fileName;

	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		system("cls");
		std::cout << "Could not open file with name " << fileName << std::endl;
		return;
	}

	for (size_t i = 0; i < container.size(); i++)
	{
		ofs << container[i].toString() << std::endl;
	}

	system("cls");
	std::cout << "Figures saves successfully!" << std::endl;
	ofs.close();
}

int main()
{
	//get the desired factory
	std::unique_ptr<BaseFactory> factory = getFactory();

	//generate N figures
	bool isContanerFilled = false;
	FigureContainer container;
	while (!isContanerFilled)
	{
		isContanerFilled = fillContainerWithFiguresFromFactory(container, factory, getCountFiguresToGenerate());
		if (!isContanerFilled)
		{
			factory = getFactory();
		}
	}

	//get user operations
	while (true)
	{
		printMainOperations();

		int index;
		if (!getUserIndex(index, 1, 5))
			continue;

		switch (index)
		{
		case 1:
			system("cls");
			printAllFigures(container);
			break;
		case 2:
			removeFigure(container);
			break;
		case 3:
			dublicateFigure(container);
			break;
		case 4:
			saveToFile(container);
			break;
		case 5:
			return 0;
		default:
			break;
		}
	}
}

