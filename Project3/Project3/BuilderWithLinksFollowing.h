#pragma once
#include <filesystem>
#include <unordered_set>
#include "BuilderBase.h"

namespace fs = std::filesystem;

class BuilderWithLinksFollowing : public BuilderBase
{
private:
	std::unordered_set<std::string> usedDirectories;
	fs::path getTargetPathFromShortcut(const fs::path& pathToShortcut);
	std::unique_ptr<Directory> buildRecursively(const fs::path& targetDir, const std::string& currPath = "");
public:
	void build(const std::string& targetDirectoryPath) override;
};
