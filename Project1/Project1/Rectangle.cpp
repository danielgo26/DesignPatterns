#include "Rectangle.h"

const short Rectangle::rectangleEdges = 2;

Rectangle::Rectangle(double sideA, double sideB)
	:Rectangle(std::move(std::vector<double>{ sideA, sideB })) {}

Rectangle::Rectangle(std::vector<double> determiningEdges)
	:Figure(std::move(determiningEdges))
{
	if (this->determiningEdges.size() != Rectangle::rectangleEdges)
		throw std::length_error("The figure does not have valid count of given edges.");

	for (size_t i = 0; i < Rectangle::rectangleEdges; i++)
	{
		if (this->determiningEdges[i] <= 0)
			throw std::invalid_argument("A side cannot have a non-positive value!");
	}
	std::sort(this->determiningEdges.begin(), this->determiningEdges.end());
}

//The base class implementation fulfills the rectangle's class definition for equality
bool Rectangle::operator==(const Figure& other) const
{
	return Figure::operator==(other);
}

std::unique_ptr<Figure> Rectangle::clone() const
{
	return std::make_unique<Rectangle>(*this);
}

double Rectangle::getPerimeter() const
{
	return 2 * (this->determiningEdges[0] + this->determiningEdges[1]);
}

std::string Rectangle::toString() const
{
	return "rectangle " + Figure::toString();
}

std::vector<double> Rectangle::readDeterminingEdgesFromStream(std::istream& is)
{
	return Figure::readDeterminingEdgesFromStream(is, Rectangle::rectangleEdges);
}