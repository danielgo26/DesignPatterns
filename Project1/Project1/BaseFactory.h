#pragma once
#include <memory>
#include <random>

//BaseFactory is an abstract base class of all the factories that will be responsible for creating objects
//It gives a common interface (create function) of all of its derivatives
//Used for the abstract factory dessign pattern implementation

class Figure;
class BaseFactory
{
public:
	virtual std::unique_ptr<Figure> create() = 0;
	virtual ~BaseFactory() = default;
};
