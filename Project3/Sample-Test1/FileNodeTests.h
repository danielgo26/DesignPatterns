#pragma once
#include "gtest/gtest.h"
#include "..\Project3\FileNode.h"
#include "..\Project3\FolderNode.h"
#include "..\Project3\GeneratorBase.h"
#include <stdexcept>

class MockFileGenerator : public GeneratorBase {
public:
	struct state
	{
		std::string type;
		std::string path;
	};
	
	state innerState;
	MockFileGenerator()
		:GeneratorBase(nullptr) {}
	void visitFile(FileNode* file) override
	{
		this->innerState = { "file", file->getFullPath() };
	}
	void visitFolder(FolderNode* folder) override
	{
		this->innerState = { "folder", folder->getFullPath() };
	}
};

TEST(FileNodeTest, ConstructorTest) {
	FileNode file("relative/path", "/full/path", 1024, true);

	EXPECT_EQ(file.getRelativePath(), "relative/path");
	EXPECT_EQ(file.getFullPath(), "/full/path");
	EXPECT_EQ(file.getByteSize(), 1024);
	EXPECT_TRUE(file.getShouldFollowPath());
}

TEST(FileNodeTest, SettersTest) {
	FileNode file("relative/path", "/full/path", 1024, true);

	file.setRelativePath("new/relative/path");
	file.setFullPath("/new/full/path");
	file.setByteSize(2048);

	EXPECT_EQ(file.getRelativePath(), "new/relative/path");
	EXPECT_EQ(file.getFullPath(), "/new/full/path");
	EXPECT_EQ(file.getByteSize(), 2048);
}

TEST(FileNodeTest, EqualityTest) {
	FileNode file1("path1", "/path1", 1024, true);
	FileNode file2("path1", "/path1", 1024, true);
	FileNode file3("path2", "/path2", 2048, false);

	EXPECT_TRUE(file1 == file2);
	EXPECT_FALSE(file1 == file3);
}

TEST(FileNodeTest, AcceptTest) {
	FileNode file("relative/path", "/full/path/file", 1024, true);
	MockFileGenerator mockGenerator;

	file.accept(&mockGenerator);

	EXPECT_EQ(strcmp(mockGenerator.innerState.type.c_str(),"file"), 0);
	EXPECT_EQ(strcmp(mockGenerator.innerState.path.c_str(), "/full/path/file"), 0);
}

