#pragma once
#include <filesystem>
#include "BuilderBase.h"

namespace fs = std::filesystem;

class BuilderWithoutLinksFollowing : public BuilderBase
{
private:
	std::unique_ptr<Directory> buildRecursively(const fs::path& targetDir,
		const std::string& currPath = "");
public:
	void build(const std::string& targetDirectoryPath) override;
};