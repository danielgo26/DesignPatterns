#pragma once
#include "GeneratorBase.h"
#include <iostream>

class ReportGenerator : public GeneratorBase
{
public:
	ReportGenerator(std::unique_ptr<FileNodeOperator> fileOperator, std::ostream* os = &std::cout);
	void visitFile(FileNode* file) override;
	void visitFolder(FolderNode* folder) override;
};