#pragma once
#include <iostream>

#include "FileNodeOperator.h"
class FolderNode;

class GeneratorBase
{
protected:
	std::ostream* os = nullptr;
	std::unique_ptr<FileNodeOperator> fileOperator = nullptr;
	int aligningSpaces = 0;
public:
	GeneratorBase(std::unique_ptr<FileNodeOperator> fileOperator, std::ostream* os = &std::cout);
	void resetOutputStream(std::ostream* os);
	virtual void visitFile(FileNode* file) = 0;
	virtual void visitFolder(FolderNode* file) = 0;

	virtual ~GeneratorBase() = default;
};
