#include "RandomFactory.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <iostream>

RandomFactory::RandomFactory(size_t countFigureTypes, double upperBoundary)
	:gen(rd()), countFigureTypes(countFigureTypes), upperBoundaryFigureEdge(upperBoundary) {}

template <typename T>
T RandomFactory::generateRandomNumber(T min, T max) const {
	std::uniform_real_distribution<> distrib(min, max);
	return distrib(gen);
}

std::unique_ptr<Figure> RandomFactory::create()
{
	int typeOfFigureByIndex = this->generateRandomNumber<int>(0, this->countFigureTypes);

	std::vector<double> determiningEdges;
	switch (typeOfFigureByIndex)
	{
		//circle
	case 0:
		determiningEdges.push_back(this->generateRandomNumber<double>(1, this->upperBoundaryFigureEdge));

		return std::make_unique<Circle>(determiningEdges);
		//rectangle
	case 1:
		determiningEdges.push_back(this->generateRandomNumber<double>(1, this->upperBoundaryFigureEdge));
		determiningEdges.push_back(this->generateRandomNumber<double>(1, this->upperBoundaryFigureEdge));

		return std::make_unique<Rectangle>(determiningEdges);
		//triangle
	case 2:
		determiningEdges.push_back(this->generateRandomNumber<double>(1, this->upperBoundaryFigureEdge));
		determiningEdges.push_back(this->generateRandomNumber<double>(1, this->upperBoundaryFigureEdge));
		determiningEdges.push_back(this->generateRandomNumber<double>(
			std::max(determiningEdges[0], determiningEdges[1]) - std::min(determiningEdges[0], determiningEdges[1]),
			determiningEdges[0] + determiningEdges[1]));

		return std::make_unique<Triangle>(determiningEdges);
	default:
		return std::unique_ptr<Figure>(new Circle(1));
	}


}