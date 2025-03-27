#include "FileNode.h"
#include "GeneratorBase.h"

FileNode::FileNode(std::string relativePath, std::string fullPath, size_t byteSize, bool shouldFollowPath)
	:Directory(std::move(relativePath), std::move(fullPath), byteSize, shouldFollowPath) {}

void FileNode::accept(GeneratorBase* visitor)
{
	//return result 
	if (visitor)
		visitor->visitFile(this);
}