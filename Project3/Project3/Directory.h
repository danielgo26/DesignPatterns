#pragma once
#include <string>
#include "GeneratorBase.h"

class Directory
{
private:
	std::string relativePath;
	std::string fullPath;
	size_t byteSize;
	bool shouldFollowPath;
protected:
	Directory(std::string relativePath, std::string fullPath, size_t byteSize, bool shouldFollowPath);
public:
	const std::string& getRelativePath() const;
	const std::string& getFullPath() const;
	void setRelativePath(const std::string& path);
	void setFullPath(const std::string& path);
	
	size_t getByteSize() const;
	void setByteSize(size_t size);

	bool getShouldFollowPath() const;

	virtual bool operator==(const Directory& other) const;

	virtual void accept(GeneratorBase* visitor) = 0;

	virtual ~Directory() = default;
};