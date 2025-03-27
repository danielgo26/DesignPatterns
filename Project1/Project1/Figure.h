#pragma once
#include<string>
#include<memory>
#include<vector>
#include<algorithm>
#include<string>
#include<sstream>

//The Figure base class provides functionalities with a default behaviour that can be used in the child classes if needed. 
//It will store a vector of a figure's edges(sides/radius) that will unify operations (like comparison, toString method and
//reading data from a stream) between all different child classes.
class Figure
{
protected:
	std::vector<double> determiningEdges;
	Figure(std::vector<double> determiningEdges);
public:
	virtual bool operator==(const Figure& other) const;
	virtual std::unique_ptr<Figure> clone() const = 0;

	virtual double getPerimeter() const = 0;
	virtual std::string toString() const;

	static std::vector<double> readDeterminingEdgesFromStream(std::istream& is, size_t edgesCount);

	virtual ~Figure() = default;
};