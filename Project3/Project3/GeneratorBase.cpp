#include <iostream>
#include "GeneratorBase.h"

GeneratorBase::GeneratorBase(std::unique_ptr<FileNodeOperator> fileOperator, std::ostream* os)
	:fileOperator(std::move(fileOperator))
{
	resetOutputStream(os);
}

void GeneratorBase::resetOutputStream(std::ostream* os)
{
	if (!os)
		throw std::invalid_argument("Output file not existing!");
	this->os = os;
}