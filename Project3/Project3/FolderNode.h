#pragma once
#include "Directory.h"
#include <vector>
#include <iostream>

class FolderNode : public Directory
{
private:
	std::vector<std::unique_ptr<Directory>> subDirectories;
public:
	FolderNode(std::string relativePath, std::string fullPath, size_t byteSize, bool shouldFollowPath = true);
	FolderNode(std::string path, std::string fullPath, size_t byteSize,
		std::vector<std::unique_ptr<Directory>> subDirectories, bool shouldFollowPath = true);

	size_t countSubDirectories() const;
	const std::unique_ptr<Directory>& getSubDirectoryAt(size_t index) const;
	void addSubDirectory(std::unique_ptr<Directory> toAdd);

	bool operator==(const Directory& other) const override;
	void accept(GeneratorBase* visitor) override;
};
