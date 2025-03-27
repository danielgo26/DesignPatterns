#pragma once
#include "Directory.h"

class BuilderBase
{
protected:
	std::unique_ptr<Directory> directoryProduct = nullptr;
public:
	virtual void build(const std::string& targetDirectoryPath) = 0;
	std::unique_ptr<Directory> getResult();
	virtual ~BuilderBase() = default;
};