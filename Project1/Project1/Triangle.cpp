#include "Triangle.h"

const short Triangle::triangleEdges = 3;

bool Triangle::assuresTrianglesInequalityLaw(double sideA, double sideB, double sideC)
{
	//validate negative values
	return !(sideA + sideB <= sideC || sideB + sideC <= sideA || sideA + sideC <= sideB);
}

Triangle::Triangle(double sideA, double sideB, double sideC)
	:Triangle(std::move(std::vector<double>{sideA, sideB, sideC})) {}


Triangle::Triangle(std::vector<double> determiningEdges)
	:Figure(std::move(determiningEdges))
{

	if (this->determiningEdges.size() != Triangle::triangleEdges)
		throw std::length_error("The figure does not have valid count of given edges.");

	for (size_t i = 0; i < Triangle::triangleEdges; i++)
	{
		if (this->determiningEdges[i] <= 0)
			throw std::invalid_argument("A side cannot have a non-positive value!");
	}

	if (!Triangle::assuresTrianglesInequalityLaw(this->determiningEdges[0], this->determiningEdges[1], this->determiningEdges[2]))
		throw std::invalid_argument("The inequality of the triangle is not met!");

	std::sort(this->determiningEdges.begin(), this->determiningEdges.end());
}

//The base class implementation fulfills the triangle's class definition for equality
bool Triangle::operator==(const Figure& other) const
{
	return Figure::operator==(other);
}

std::unique_ptr<Figure>	Triangle::clone() const
{
	return std::make_unique<Triangle>(*this);
}

double Triangle::getPerimeter() const
{
	return this->determiningEdges[0] + this->determiningEdges[1] + this->determiningEdges[2];
}

std::string Triangle::toString() const
{
	return "triangle " + Figure::toString();
}

std::vector<double> Triangle::readDeterminingEdgesFromStream(std::istream& is)
{
	return Figure::readDeterminingEdgesFromStream(is, Triangle::triangleEdges);
}