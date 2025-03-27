#pragma once
#include "gtest/gtest.h"
#include "..\Project3\BuilderWithoutLinksFollowing.h"
#include "..\Project3\FolderNode.h"
#include "..\Project3\FileNode.h"

TEST(BuilderWithoutLinksFollowing, buildValidHierarchyWithShortcutToFile)
{
	BuilderWithoutLinksFollowing builder;

	builder.build(".\\Resourses\\Shortcut.lnk");

	std::unique_ptr<FileNode> expected = std::move(std::make_unique<FileNode>
		("Shortcut.lnk", ".\\Resourses\\Shortcut.lnk", fs::file_size(".\\Resourses\\Shortcut.lnk"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());

	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithoutLinksFollowing, buildValidHierarchyWithShortcutToFolder)
{
	BuilderWithoutLinksFollowing builder;

	builder.build(".\\Resourses\\ShortcutToFolder.lnk");

	std::unique_ptr<FileNode> expected = std::move(std::make_unique<FileNode>
		("ShortcutToFolder.lnk", ".\\Resourses\\ShortcutToFolder.lnk", fs::file_size(".\\Resourses\\ShortcutToFolder.lnk"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());

	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithoutLinksFollowing, buildValidHierarchyWithSymlinkToFile)
{
	BuilderWithoutLinksFollowing builder;

	builder.build(".\\Resourses\\SymlinkToFile");

	std::unique_ptr<FileNode> expected = std::move(std::make_unique<FileNode>
		("SymlinkToFile.symlink", ".\\Resourses\\SymlinkToFile", fs::file_size(".\\Resourses\\SymlinkToFile"), false));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithoutLinksFollowing, buildValidHierarchyWithSymlinkToFolder)
{
	BuilderWithoutLinksFollowing builder;

	builder.build(".\\Resourses\\SymlinkToFolder");

	std::unique_ptr<FolderNode> expected = std::move(std::make_unique<FolderNode>
		("SymlinkToFolder.symlink", ".\\Resourses\\SymlinkToFolder", fs::file_size(".\\Resourses\\SymlinkToFolder"), false));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithoutLinksFollowing, buildValidHierarchyWithFile)
{
	BuilderWithoutLinksFollowing builder;

	builder.build(".\\Resourses\\File.txt");

	std::unique_ptr<FileNode> expected = std::move(std::make_unique<FileNode>
		("File.txt", ".\\Resourses\\File.txt", fs::file_size(".\\Resourses\\File.txt"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithoutLinksFollowing, buildValidHierarchyWithFolderWithoutSubdirectories)
{
	BuilderWithoutLinksFollowing builder;

	builder.build(".\\Resourses\\Folder");

	std::unique_ptr<FolderNode> expected = std::move(std::make_unique<FolderNode>
		("Folder", ".\\Resourses\\Folder", fs::file_size(".\\Resourses\\Folder"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithoutLinksFollowing, buildValidHierarchyWithFolderWithSubdirectories)
{
	BuilderWithoutLinksFollowing builder;

	builder.build(".\\Resourses\\FolderWithSubdirectories");

	std::unique_ptr<FolderNode> subDir1 = std::move(std::make_unique<FolderNode>
		("FolderWithSubdirectories\\SubDir1", ".\\Resourses\\FolderWithSubdirectories\\SubDir1",
			fs::file_size(".\\Resourses\\FolderWithSubdirectories\\SubDir1"), true));

	std::unique_ptr<FileNode> subDir2 = std::move(std::make_unique<FileNode>
		("FolderWithSubdirectories\\SubDir2.txt", ".\\Resourses\\FolderWithSubdirectories\\SubDir2.txt",
			fs::file_size(".\\Resourses\\FolderWithSubdirectories\\SubDir2.txt"), true));

	std::vector<std::unique_ptr<Directory>> subdirs;
	subdirs.push_back(std::move(subDir1));
	subdirs.push_back(std::move(subDir2));

	std::unique_ptr<FolderNode> expected = std::move(std::make_unique<FolderNode>
		("FolderWithSubdirectories", ".\\Resourses\\FolderWithSubdirectories",
			fs::file_size(".\\Resourses\\FolderWithSubdirectories"), std::move(subdirs), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithoutLinksFollowing, buildDirectoryWithErrorStateFileNode)
{
	BuilderWithoutLinksFollowing builder;

	builder.build(".\\Resourses\\unexisting.txt");

	std::unique_ptr<FileNode> expected = std::move(std::make_unique<FileNode>
		("[error reading directory...not able to continue]", ".\\Resourses\\unexisting.txt", 0, false));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithoutLinksFollowing, buildDirectoryWithErrorStateSubDirectory)
{
	BuilderWithoutLinksFollowing builder;

	builder.build(".\\Resourses\\FolderWithErrorSubDirectory");

	std::unique_ptr<FileNode> subDir1 = std::move(std::make_unique<FileNode>
		("FolderWithErrorSubDirectory\\ShortcutToDeletedFile.lnk",
			".\\Resourses\\FolderWithErrorSubDirectory\\ShortcutToDeletedFile.lnk", 
			fs::file_size(".\\Resourses\\FolderWithErrorSubDirectory\\ShortcutToDeletedFile.lnk"), true));

	std::vector<std::unique_ptr<Directory>> subdirs;
	subdirs.push_back(std::move(subDir1));

	std::unique_ptr<FolderNode> expected = std::move(std::make_unique<FolderNode>
		("FolderWithErrorSubDirectory", ".\\Resourses\\FolderWithErrorSubDirectory",
			fs::file_size(".\\Resourses\\FolderWithErrorSubDirectory\\ShortcutToDeletedFile.lnk"), std::move(subdirs), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());

	EXPECT_TRUE(expected->operator==(*result.get()));
}