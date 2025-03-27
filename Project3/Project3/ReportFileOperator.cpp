#include "ReportFileOperator.h"
#include "FileNode.h"

bool ReportFileOperator::doGatherData(const FileNode* file, const std::unique_ptr<ChecksumCalculator>& hashCalculator)
{
	if (!file)
		return false;

	byteSize = file->getByteSize();
	path = file->getRelativePath();

	return true;
}

bool ReportFileOperator::doProcessData(std::ostream& os, int aligningSpaces)
{
	if (!os.good())
		return false;

	for (size_t i = 0; i < aligningSpaces; i++)
	{
		os << " ";
	}
	os << path << " " << "(" << byteSize << " bytes)" << std::endl;

	return true;
}