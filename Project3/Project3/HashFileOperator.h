#pragma once
#include "FileNodeOperator.h"

class HashFileOperator : public FileNodeOperator
{
private:
	std::string generatedHash = "";
	std::string path = "";
public:
	bool doGatherData(const FileNode* file,
		const std::unique_ptr<ChecksumCalculator>& hashCalculator) override;
	bool doProcessData(std::ostream& os, int aligningSpaces = 0) override;
};