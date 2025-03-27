#include "FolderNode.h"
#include <iostream>

FolderNode::FolderNode(std::string relativePath, std::string fullPath, size_t byteSize, bool shouldFollowPath)
	:Directory(std::move(relativePath), std::move(fullPath), byteSize, shouldFollowPath) {}

FolderNode::FolderNode(std::string relativePath, std::string fullPath, size_t byteSize,
	std::vector<std::unique_ptr<Directory>> subDirectories, bool shouldFollowPath)
	:FolderNode(std::move(relativePath), std::move(fullPath), byteSize, shouldFollowPath)
{
	for (size_t i = 0; i < subDirectories.size(); i++)
	{
		if (!subDirectories[i])
			throw std::invalid_argument("Directory is not existing!");
	}
	this->subDirectories = std::move(subDirectories);
}

size_t FolderNode::countSubDirectories() const
{
	return this->subDirectories.size();
}

const std::unique_ptr<Directory>& FolderNode::getSubDirectoryAt(size_t index) const
{
	if (index >= 0 && index < this->subDirectories.size())
		return this->subDirectories[index];
	return nullptr;
}

void FolderNode::addSubDirectory(std::unique_ptr<Directory> toAdd)
{
	if (!toAdd)
		throw std::invalid_argument("Directory is not existing!");
	this->subDirectories.push_back(std::move(toAdd));
}

bool FolderNode::operator==(const Directory& other) const
{
	if (!this->Directory::operator==(other))
		return false;

	const FolderNode* castedOther = dynamic_cast<const FolderNode*>(&other);
	if (!castedOther || this->subDirectories.size() != castedOther->subDirectories.size())
		return false;

	for (size_t i = 0; i < this->subDirectories.size(); i++)
	{
		if (!(this->subDirectories[i]->operator==(*castedOther->subDirectories[i].get())))
			return false;
	}
	return true;
}

void FolderNode::accept(GeneratorBase* visitor)
{
	if (visitor)
		visitor->visitFolder(this);
}