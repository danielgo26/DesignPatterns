#pragma once
#include "Figure.h"

//Two rectangles are equal only when they have the same length of sides and are given in the exact same order:
//rectangle rotation will differ two when compared.
//For that reason, the Rectangle class will keep rectangles's sides sorted.
//The Rectangle constructor will throw if invalid data is passed, so the calling it block should manage the exception.
//The Rectangle class is aware how to read data from a stream needed for the creation of its instances.

class Rectangle : public Figure
{
private:
	static const short rectangleEdges;
public:
	Rectangle(double sideA, double sideB);
	Rectangle(std::vector<double> determiningEdges);

	bool operator==(const Figure& other) const override;
	std::unique_ptr<Figure> clone() const override;

	double getPerimeter() const override;
	std::string toString() const override;
	static std::vector<double> readDeterminingEdgesFromStream(std::istream& is);
};