#pragma once
#include "BaseFactory.h"

//The random factory will manage the random creation of a figure
//It takes two paramethers with a default value in its constructor - the count of figure types it will support generating
//and a upper boundary until with it will generate edge's values
//It generates the triangle figure with taking into account the inequality of a triangle rule in order
//to generate valid triangles
//For further added figures it will depand their validation logic put here(like the triangle one), instead creating
//the figure first and then checking its correctness. Otherwise it can slow the current execution.

class RandomFactory : public BaseFactory
{
private:
	std::random_device rd;
	mutable std::mt19937 gen;
	size_t countFigureTypes = 3;
	double upperBoundaryFigureEdge = 100;

	template <typename T>
	T generateRandomNumber(T min, T max) const;
public:
	RandomFactory(size_t countFigureTypes = 3, double upperBoundary = 100);
	virtual std::unique_ptr<Figure> create() override;
};
