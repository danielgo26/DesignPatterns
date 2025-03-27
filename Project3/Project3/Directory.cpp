#include "Directory.h"

Directory::Directory(std::string relativePath, std::string fullPath, size_t byteSize, bool shouldFollowPath)
	:relativePath(std::move(relativePath)), fullPath(std::move(fullPath)),
	byteSize(byteSize), shouldFollowPath(shouldFollowPath) {}

const std::string& Directory::getRelativePath() const
{
	return this->relativePath;
}

const std::string& Directory::getFullPath() const
{
	return this->fullPath;
}

void Directory::setRelativePath(const std::string& path)
{
	this->relativePath = path;
}

void Directory::setFullPath(const std::string& path)
{
	this->fullPath = path;
}

size_t Directory::getByteSize() const
{
	return this->byteSize;
}

void Directory::setByteSize(size_t size)
{
	this->byteSize = size;
}

bool Directory::getShouldFollowPath() const
{
	return this->shouldFollowPath;
}

bool Directory::operator==(const Directory& other) const
{
	return this->byteSize == other.byteSize && this->relativePath == other.relativePath
		&& this->fullPath == other.fullPath && this->shouldFollowPath == other.shouldFollowPath;
}