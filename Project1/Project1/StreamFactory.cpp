#include "StreamFactory.h"
#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

StreamFactory::StreamFactory(std::istream& stream) :stream(stream)
{
	if (!stream)
		throw std::invalid_argument("The stream is not opened correctly!");
}

StreamFactory::StreamFactory(std::ifstream&& file) :file(std::move(file)), stream(this->file)
{
	if (!this->file)
		throw std::invalid_argument("The file is not found or could not be opened!");
}

std::unique_ptr<Figure> StreamFactory::create()
{
	if (!this->stream)
		throw std::invalid_argument("The file is not found or could not be opened!");

	if (!this->file.is_open())
	{
		std::cout << "Enter the figure data in the format: [name] [side1, side2, ... , sideN]:" << std::endl;
	}

	std::string nameOfFigure;
	stream >> nameOfFigure;

	try
	{
		if (nameOfFigure == "rectangle")
		{
			return std::make_unique<Rectangle>(Rectangle::readDeterminingEdgesFromStream(stream));
		}
		else if (nameOfFigure == "triangle")
		{
			return std::make_unique<Triangle>(Triangle::readDeterminingEdgesFromStream(stream));
		}
		else if (nameOfFigure == "circle")
		{
			return std::make_unique<Circle>(Circle::readDeterminingEdgesFromStream(stream));
		}
	}
	catch (const std::invalid_argument& e)
	{
		//read the next given data if the argument list is invalid
		char buff[1024];
		stream.getline(buff, 1024);
		throw;
	}

	if (nameOfFigure == "")
		throw std::logic_error("No existing figures to be read!");

	//read the next given data if the name is invalid
	char buff[1024];
	stream.getline(buff, 1024);
	throw std::invalid_argument("Invalid name(\"" + nameOfFigure + "\") of figure!");
}