#pragma once
#include "Directory.h"

class FileNode : public Directory
{
public:
	FileNode(std::string relativePath, std::string fullPath, size_t byteSize, bool shouldFollowPath = true);
	void accept(GeneratorBase* visitor) override;
};
