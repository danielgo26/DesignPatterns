#include "FigureContainer.h"

inline size_t FigureContainer::size() const
{
	return this->figures.size();
}

const Figure& FigureContainer::operator[](size_t index) const
{
	if (index >= this->size())
		throw std::out_of_range("Index out of range");

	return *(this->figures[index]);
}

void FigureContainer::moveToCollection(std::unique_ptr<Figure> figure)
{
	this->figures.push_back(std::move(figure));
}

void FigureContainer::removeAt(size_t index)
{
	if (index >= this->size())
		throw std::out_of_range("Index out of range");

	this->figures.erase(this->figures.begin() + index);
}

void FigureContainer::clear()
{
	this->figures.clear();
}