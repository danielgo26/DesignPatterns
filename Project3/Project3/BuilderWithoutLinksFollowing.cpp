#include <unordered_set>

#include "BuilderWithoutLinksFollowing.h"
#include "FileNode.h"
#include "FolderNode.h"

using namespace std;

std::unique_ptr<Directory> BuilderWithoutLinksFollowing::buildRecursively(const fs::path& targetDir,
	const std::string& currPath)
{
	if (!fs::exists(targetDir))
		return std::make_unique<FileNode>(currPath +
			"[error reading directory...not able to continue]", targetDir.string(), 0, false);

	if (fs::is_symlink(targetDir))
	{
		if (fs::is_regular_file(targetDir))
			return std::move(std::make_unique<FileNode>
				(currPath + targetDir.filename().string() + ".symlink", targetDir.string(), 0, false));
		return std::move(std::make_unique<FolderNode>
			(currPath + targetDir.filename().string() + ".symlink", targetDir.string(), 0, false));
	}
	else
	{
		if (fs::is_regular_file(targetDir)) {
			return std::move(std::make_unique<FileNode>(currPath + targetDir.filename().string(),
				targetDir.string(), fs::file_size(targetDir)));
		}
		std::string newCurrPath = currPath + targetDir.filename().string();
		std::unique_ptr<FolderNode> currFolder = std::make_unique<FolderNode>(newCurrPath, targetDir.string(), 0);

		try {
			// Iterate through all entries(files and folders) in the directory
			for (const auto& entry : fs::directory_iterator(targetDir))
			{
				std::unique_ptr<Directory> subDirectory = std::move(buildRecursively(entry.path(),
					newCurrPath + "\\"));
				currFolder->setByteSize(currFolder->getByteSize() + subDirectory->getByteSize());
				currFolder->addSubDirectory(std::move(subDirectory));
			}
		}
		catch (...) {
			currFolder->setByteSize(currFolder->getByteSize());
			currFolder->addSubDirectory(std::make_unique<FileNode>
				(newCurrPath + "\\[error reading directory...not able to continue]", targetDir.string(), 0, false));
		}

		return std::move(currFolder);
	}
}

void BuilderWithoutLinksFollowing::build(const std::string& targetDirectoryPath)
{
	this->directoryProduct = std::move(this->buildRecursively(targetDirectoryPath));
}