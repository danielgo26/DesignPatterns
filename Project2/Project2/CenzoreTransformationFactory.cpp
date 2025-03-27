#include "CenzoreTransformationFactory.h"

const size_t CenzoreTransformationFactory::flyweightMaxObjectsSize = 4;
std::map<std::string, std::shared_ptr<TextTransformation>> CenzoreTransformationFactory::cenzores =
std::map<std::string, std::shared_ptr<TextTransformation>>();

std::shared_ptr<TextTransformation> CenzoreTransformationFactory::getCenzoreTransformation(const std::string& toCenzore)
{
	if (toCenzore.size() > flyweightMaxObjectsSize)
		return std::make_shared<CenzoreTransformation>(toCenzore);

	if (cenzores.count(toCenzore) == 0)
		cenzores[toCenzore] = std::make_shared<CenzoreTransformation>(toCenzore);

	return cenzores[toCenzore];
}