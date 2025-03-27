#pragma once
#include "Figure.h"

//Two triangles are equal only when they have the same length of sides and are given in the exact same order:
//triangle rotation will differ two when compared.
//For that reason, the Triangle class will keep triangle's sides sorted.
//The Triangle constructor will throw if invalid data is passed, so the calling it block should manage the exception.
//The Triangle class is aware how to read data from a stream needed for the creation of its instances.

class Triangle : public Figure
{
private:
	static const short triangleEdges;
	static bool assuresTrianglesInequalityLaw(double sideA, double sideB, double sideC);
public:
	Triangle(double sideA, double sideB, double sideC);
	Triangle(std::vector<double> determiningEdges);

	bool operator==(const Figure& other) const override;
	std::unique_ptr<Figure> clone() const override;

	double getPerimeter() const override;
	std::string toString() const override;
	static std::vector<double> readDeterminingEdgesFromStream(std::istream& is);
};