#include "Circle.h"
#include <corecrt_math_defines.h>

const short Circle::circleEdges = 1;

Circle::Circle(double radius)
	:Circle(std::move(std::vector<double>{ radius })) {}

Circle::Circle(std::vector<double> determiningEdges)
	:Figure(std::move(determiningEdges))
{
	if (this->determiningEdges.size() != Circle::circleEdges)
		throw std::length_error("The figure does not have valid count of given edges.");

	if (this->determiningEdges[0] <= 0)
		throw std::invalid_argument("The radius cannot have a non-positive value!");
}

//The base class implementation fulfills the circle's class definition for equality
bool Circle::operator==(const Figure& other) const
{
	return Figure::operator==(other);
}

std::unique_ptr<Figure> Circle::clone() const
{
	return std::make_unique<Circle>(*this);
}

double Circle::getPerimeter() const
{
	return 2 * M_PI * this->determiningEdges[0];
}

std::string Circle::toString() const
{
	return "circle " + Figure::toString();
}

std::vector<double> Circle::readDeterminingEdgesFromStream(std::istream& is)
{
	return Figure::readDeterminingEdgesFromStream(is, Circle::circleEdges);
}