#pragma once
#include <iostream>
#include <map>
#include "CenzoreTransformation.h"

/// <summary>
/// Factory responsible for specificly cenzore transformation creation
/// The factory stores immutable flyweight objects under the flyweightMaxObjectsSize property
/// The getCenzoreTransformation() function determines if it will create a new object or will return a flyweight one, so
/// the factory is responsible for the management of the flyweight object references
/// </summary>

class CenzoreTransformationFactory
{
private:
	static const size_t flyweightMaxObjectsSize;
	static std::map<std::string, std::shared_ptr<TextTransformation>> cenzores;
public:
	static std::shared_ptr<TextTransformation> getCenzoreTransformation(const std::string& toCenzore);
};