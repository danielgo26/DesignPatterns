#pragma once
#include "Figure.h"

//Two circles are equal only when they have the same radius
//The Circle constructor will throw if invalid data is passed, so the calling it block should manage the exception.
//The Circle class is aware how to read data from a stream needed for the creation of its instances.

class Circle : public Figure
{
private:
	static const short circleEdges;
public:
	Circle(double radius);
	Circle(std::vector<double> determiningEdges);

	bool operator==(const Figure& other) const override;
	std::unique_ptr<Figure> clone() const override;

	double getPerimeter() const override;
	std::string toString() const override;
	static std::vector<double> readDeterminingEdgesFromStream(std::istream& is);
};