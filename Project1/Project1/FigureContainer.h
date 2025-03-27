#pragma once
#include "Figure.h"

//The FigureContainer class as a polymorphic container, holding unique pointers of figures
//When adding a figure, it moves it to its collection, so it will be responsible for its life span
//It supports run-time check when reaching elements by index

class FigureContainer
{
private:
	std::vector<std::unique_ptr<Figure>> figures;
public:
	inline size_t size() const;

	const Figure& operator[](size_t index) const;

	void moveToCollection(std::unique_ptr<Figure> figure);
	void removeAt(size_t index);
	void clear();
};

