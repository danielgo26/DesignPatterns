#include "AbstractFactory.h"
#include "RandomFactory.h"
#include "StreamFactory.h"
#include <iostream>

std::unique_ptr<BaseFactory> AbstractFactory::create(const std::string& criteria)
{
	if (criteria == "random")
	{
		return std::make_unique<RandomFactory>();
	}
	else if (criteria == "stdin")
	{
		return std::make_unique<StreamFactory>(std::cin);
	}
	else if (criteria == "file")
	{
		std::cout << "Enter the name of the file to be opened: ";
		std::string fileName;
		std::cin >> fileName;
		return std::make_unique<StreamFactory>(std::ifstream(fileName));
	}
	throw std::invalid_argument("Factory with name \"" + criteria + "\" does not exist.");
}