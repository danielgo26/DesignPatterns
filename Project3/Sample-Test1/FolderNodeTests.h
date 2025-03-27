#pragma once
#include <gtest/gtest.h>
#include "..\Project3\FolderNode.h"
#include "..\Project3\FileNode.h"
#include "..\Project3\GeneratorBase.h"
#include <stdexcept>

class MockFolderGenerator : public GeneratorBase {
public:
	struct state
	{
		std::string type;
		std::string path;
	};

	state innerState;
	MockFolderGenerator()
		:GeneratorBase(nullptr) {}
	inline virtual void visitFile(FileNode* file) override
	{
		this->innerState = { "file", file->getFullPath() };
	}
	inline virtual void visitFolder(FolderNode* folder) override
	{
		this->innerState = { "folder", folder->getFullPath() };
	}
};

TEST(FolderNodeTest, ConstructorWithNoSubDirectories) {
	FolderNode folder("relative/path", "/full/path", 1024);
	EXPECT_EQ(folder.countSubDirectories(), 0);

	EXPECT_EQ(folder.getRelativePath(), "relative/path");
	EXPECT_EQ(folder.getFullPath(), "/full/path");
	EXPECT_EQ(folder.getByteSize(), 1024);
	EXPECT_TRUE(folder.getShouldFollowPath());
}

TEST(FolderNodeTest, ConstructorWithCorrectSubDirectories) {

	FileNode subFile("subfile1", "/subfile1", 50);
	FolderNode subFolder("subfolder1", "/subfolder1", 100);
	std::vector<std::unique_ptr<Directory>> subDirs;
	subDirs.push_back(std::make_unique<FileNode>
		(subFile.getRelativePath(), subFile.getFullPath(), subFile.getByteSize()));
	subDirs.push_back(std::make_unique<FolderNode>
		(subFolder.getRelativePath(), subFolder.getFullPath(), subFolder.getByteSize()));

	FolderNode folder("relative/path", "/full/path", 1000, std::move(subDirs));

	EXPECT_EQ(folder.countSubDirectories(), 2);
	EXPECT_EQ(strcmp(folder.getRelativePath().c_str(), "relative/path"), 0);
	EXPECT_EQ(strcmp(folder.getFullPath().c_str(), "/full/path"), 0);
	EXPECT_EQ(folder.getByteSize(), 1000);
	EXPECT_TRUE(folder.getShouldFollowPath());

	EXPECT_TRUE(folder.getSubDirectoryAt(0)->operator==(subFile));
	EXPECT_TRUE(folder.getSubDirectoryAt(1)->operator==(subFolder));
}

TEST(FolderNodeTest, ConstructorWithIncorrectSubDirectories) {

	FileNode file("subdir1", "/subdir1", 512);
	std::vector<std::unique_ptr<Directory>> subDirs;
	subDirs.push_back(std::make_unique<FolderNode>
		(file.getRelativePath(), file.getFullPath(), file.getByteSize()));
	subDirs.push_back(nullptr);

	try {
		FolderNode folder("relative/path", "/full/path", 1024, std::move(subDirs));
		FAIL() << "Expected std::runtime_error to be thrown.";
	}
	catch (const std::invalid_argument& e) {
		EXPECT_STREQ(e.what(), "Directory is not existing!");
	}
	catch (...) {
		FAIL() << "Expected std::runtime_error, but caught a different exception.";
	}
}

TEST(FolderNodeTest, SettersTest) {
	FolderNode folder("relative/path", "/full/path", 1024, true);

	folder.setRelativePath("new/relative/path");
	folder.setFullPath("/new/full/path");
	folder.setByteSize(2048);

	EXPECT_EQ(folder.getRelativePath(), "new/relative/path");
	EXPECT_EQ(folder.getFullPath(), "/new/full/path");
	EXPECT_EQ(folder.getByteSize(), 2048);
}

TEST(FolderNodeTest, AddSubDirectory) {
	FolderNode folder("relative/path", "/full/path", 1024);
	FolderNode toAdd("somePath/path", "/someFull/path", 128);

	folder.addSubDirectory(std::make_unique<FolderNode>
		(toAdd.getRelativePath(), toAdd.getFullPath(), toAdd.getByteSize()));

	EXPECT_EQ(folder.countSubDirectories(), 1);
	EXPECT_TRUE(folder.getSubDirectoryAt(0)->operator==(toAdd));
}

TEST(FolderNodeTest, AddNullSubDirectory) {
	FolderNode folder("relative/path", "/full/path", 1024);

	try {
		folder.addSubDirectory(nullptr);
		FAIL() << "Expected std::runtime_error to be thrown.";
	}
	catch (const std::invalid_argument& e) {
		EXPECT_STREQ(e.what(), "Directory is not existing!");
	}
	catch (...) {
		FAIL() << "Expected std::runtime_error, but caught a different exception.";
	}
}
TEST(FolderNodeTest, EqualityOperatorWithoutSubdirectories) {
	FolderNode folder1("relative/path", "/full/path", 1024);
	FolderNode folder2("relative/path", "/full/path", 1024);

	EXPECT_TRUE(folder1.operator==(folder2));
}

TEST(FolderNodeTest, EqualityOperatorWithSubdirectories) {
	FolderNode folder1("relative/path", "/full/path", 1024);
	folder1.addSubDirectory(std::make_unique<FolderNode>("subdir1", "/subdir1", 512));

	FolderNode folder2("relative/path", "/full/path", 1024);
	folder2.addSubDirectory(std::make_unique<FolderNode>("subdir1", "/subdir1", 512));

	EXPECT_TRUE(folder1.operator==(folder2));
}

TEST(FolderNodeTest, InequalityOperatorWithDifferentTypeOfDirectories) {
	FolderNode folder1("relative/path", "/full/path", 1024);
	FileNode folder2("relative/path", "/full/path", 1024);

	EXPECT_FALSE(folder1.operator==(folder2));
}

TEST(FolderNodeTest, InequalityOperatorWithDifferentPath) {
	FolderNode folder1("relative/path1", "/full/path", 1024);
	folder1.addSubDirectory(std::make_unique<FolderNode>("subdir1", "/subdir1", 512));

	FolderNode folder2("relative/path2", "/full/path", 1024);
	folder2.addSubDirectory(std::make_unique<FolderNode>("subdir1", "/subdir1", 512));

	EXPECT_FALSE(folder1.operator==(folder2));
}

TEST(FolderNodeTest, InequalityOperatorWithDifferentSubdirectories) {
	FolderNode folder1("relative/path", "/full/path", 1024);
	folder1.addSubDirectory(std::make_unique<FolderNode>("subdir1", "/subdir1", 512));

	FolderNode folder2("relative/path", "/full/path", 1024);
	folder2.addSubDirectory(std::make_unique<FolderNode>("subdir2", "/subdir1", 512));

	EXPECT_FALSE(folder1.operator==(folder2));
}

TEST(FolderNodeTest, AcceptMethod) {
	FolderNode folder("relative/path", "/full/path/folder", 1024);
	MockFolderGenerator mockGenerator;

	folder.accept(&mockGenerator);

	EXPECT_EQ(strcmp(mockGenerator.innerState.type.c_str(), "folder"), 0);
	EXPECT_EQ(strcmp(mockGenerator.innerState.path.c_str(), "/full/path/folder"), 0);
}