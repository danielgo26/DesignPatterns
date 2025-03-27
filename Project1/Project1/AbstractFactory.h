#pragma once
#include <string>
#include "BaseFactory.h"
#include <memory>

//An abstract factory class which will create a corresponding figure factory by the given arguments 
//Abstract factory dessign pattern used

class AbstractFactory
{
public:
	static std::unique_ptr<BaseFactory> create(const std::string& criteria);
};
