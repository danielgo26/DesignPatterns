#include <iostream>
#include "BuilderBase.h"

std::unique_ptr<Directory> BuilderBase::getResult()
{
	std::unique_ptr<Directory> toReturn = std::move(this->directoryProduct);
	this->directoryProduct = nullptr;
	return std::move(toReturn);
}