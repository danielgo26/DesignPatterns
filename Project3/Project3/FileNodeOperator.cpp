#include "FileNodeOperator.h"

bool FileNodeOperator::operateWithFileNode(const FileNode* file, std::ostream& os,
	const std::unique_ptr<ChecksumCalculator>& hashCalculator, int aligningSpaces)
{
	if (!file || !os.good())
		return false;

	if (!this->doGatherData(file, hashCalculator))
	{
		throw std::runtime_error("Could not obtain the file's data!");
	}
	if (!this->doProcessData(os, aligningSpaces))
	{
		throw std::runtime_error("Could not process the file's data!");
	}

	return true;
}