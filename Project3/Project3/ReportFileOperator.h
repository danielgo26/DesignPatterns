#pragma once
#include "FileNodeOperator.h"

class ReportFileOperator : public FileNodeOperator
{
private:
	size_t byteSize;
	std::string path;
public:
	bool doGatherData(const FileNode* file,
		const std::unique_ptr<ChecksumCalculator>& hashCalculator = nullptr) override;
	bool doProcessData(std::ostream& os, int aligningSpaces = 0) override;
};
