#pragma once
#include "ChecksumCalculator.h"

class Observable;
class FileNode;

class FileNodeOperator
{
protected:
	virtual bool doGatherData(const FileNode* fileNode,
		const std::unique_ptr<ChecksumCalculator>& hashCalculator = nullptr) = 0;
	virtual bool doProcessData(std::ostream& os, int aligningSpaces = 0) = 0;
public:
	virtual bool operateWithFileNode(const FileNode* fileNode, std::ostream& os,
		const std::unique_ptr<ChecksumCalculator>& hashCalculator = nullptr, int aligningSpaces = 0) final;
	virtual ~FileNodeOperator() = default;
};
