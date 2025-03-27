#pragma once
#include <fstream>
#include "BaseFactory.h"

//The stream factory will manage the creation of a specific figure from a stream
//It holds two streams in it as it can operate both with the standart input stream and a file stream 
//The factory will throw if the figure cannot be created.

class StreamFactory: public BaseFactory
{
private:
	std::istream& stream;
	std::ifstream file;

public:
	StreamFactory(std::istream& is);
	StreamFactory(std::ifstream&& file);
	virtual std::unique_ptr<Figure> create() override;
};
