#include <fstream>
#include <sstream>
#include <filesystem>

#include "HashFileOperator.h"
#include "FileNode.h"

bool HashFileOperator::doGatherData(const FileNode* file, const std::unique_ptr<ChecksumCalculator>& hashCalculator)
{
	if (!file || !hashCalculator)
		return false;

	this->path = file->getRelativePath();
	if (!file->getShouldFollowPath())
	{
		try
		{
			std::string contentOfSymlink = std::filesystem::read_symlink(file->getFullPath()).string();
			std::stringstream ss(contentOfSymlink);
			this->generatedHash = hashCalculator->calculate(ss);
		}
		catch (const std::exception&)
		{
			return false;
		}
	}
	else
	{
		std::ifstream ifs(file->getFullPath(), std::ios::binary);
		if (!ifs.is_open())
			return false;

		try
		{
			this->generatedHash = hashCalculator->calculate(ifs);
		}
		catch (const std::exception&)
		{
			return false;
		}
	}

	return true;
}

bool HashFileOperator::doProcessData(std::ostream& os, int aligningSpaces)
{
	if (!os.good())
		return false;

	for (size_t i = 0; i < aligningSpaces; i++)
	{
		os << " ";
	}
	os << this->path << " (hash: " << this->generatedHash << ")" << std::endl;

	return true;
}