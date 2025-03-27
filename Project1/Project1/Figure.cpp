#include "Figure.h"

Figure::Figure(std::vector<double> determiningEdges)
	:determiningEdges(std::move(determiningEdges)) {}

bool Figure::operator==(const Figure& other) const
{
	//add check type id
	if (this->determiningEdges.size() != other.determiningEdges.size())
		return false;
	for (size_t i = 0; i < this->determiningEdges.size(); i++)
	{
		if (this->determiningEdges[i] != other.determiningEdges[i])
			return false;
	}
	return true;
}

std::string Figure::toString() const
{
	std::stringstream figureStringRepresentation;

	for (size_t i = 0; i < this->determiningEdges.size(); i++)
	{
		figureStringRepresentation << this->determiningEdges[i];
		if (i < this->determiningEdges.size() - 1)
			figureStringRepresentation << " ";
	}

	return figureStringRepresentation.str();
}

//asserts that the stream contains the floating point data needed for the figure creation
//does not check any further validation details specific for the figure
//use '.' as the sign for the decimal point
std::vector<double> Figure::readDeterminingEdgesFromStream(std::istream& is, size_t edgesCount)
{
	if (!is)
		throw std::invalid_argument("Stream not opened correctly!");

	std::vector<double> determiningEdges(edgesCount);
	for (size_t i = 0; i < edgesCount; i++)
	{
		std::string currSide;
		is >> currSide;

		//not needed, comin from stod
		//check is valid decimal non-negative number
		int countOccuranciesDecimalDot = 0;
		for (size_t i = 0; i < currSide.length(); i++)
		{
			if (currSide[i] >= '0' && currSide[i] <= '9')
				continue;
			else if (currSide[i] == '.' && countOccuranciesDecimalDot == 0)
				countOccuranciesDecimalDot++;
			else
				throw std::invalid_argument("Invalid values of the figure edges!");
		}
		//check is count of determining edges correct
		if ((i < edgesCount - 1 && is.eof()))
			throw std::length_error("Not enough edges given for creating the figure!");

		//convert to a floating point number, representing the edge length
		determiningEdges[i] = stod(currSide);
	}
	return determiningEdges;
}