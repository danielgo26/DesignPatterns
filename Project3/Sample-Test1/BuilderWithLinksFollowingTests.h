#include "gtest/gtest.h"
#include "..\Project3\BuilderWithLinksFollowing.h"
#include "..\Project3\FolderNode.h"
#include "..\Project3\FileNode.h"

TEST(BuilderWithLinksFollowing, buildValidHierarchyWithShortcutToFile)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\Shortcut.lnk");

	std::string localResoursesAbsolutePath = fs::absolute(".\\Resourses").string();
	std::unique_ptr<FileNode> expected = std::move(std::make_unique<FileNode>
		("Shortcut.lnk -(links to)-> File.txt", localResoursesAbsolutePath + "\\File.txt",
			fs::file_size(".\\Resourses\\File.txt"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());

	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithLinksFollowing, buildValidHierarchyWithShortcutToFolder)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\ShortcutToFolder.lnk");

	std::string localResoursesAbsolutePath = fs::absolute(".\\Resourses").string();
	std::unique_ptr<FolderNode> expected = std::move(std::make_unique<FolderNode>
		("ShortcutToFolder.lnk -(links to)-> Folder", localResoursesAbsolutePath + "\\Folder",
			fs::file_size(".\\Resourses\\Folder"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());

	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithLinksFollowing, buildValidHierarchyWithShortcutToShortcut)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\ShortcutToShortcut.lnk");

	std::string localResoursesAbsolutePath = fs::absolute(".\\Resourses").string();
	std::unique_ptr<FileNode> expected = std::move(std::make_unique<FileNode>
		("ShortcutToShortcut.lnk -(links to)-> File.txt",
			localResoursesAbsolutePath + "\\File.txt", fs::file_size(".\\Resourses\\File.txt"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());

	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithLinksFollowing, buildValidHierarchyWithSymlinkToFile)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\SymlinkToFile");

	std::unique_ptr<FileNode> expected = std::move(std::make_unique<FileNode>
		("SymlinkToFile.symlink -(links to)-> File.txt", ".\\Resourses\\File.txt",
			fs::file_size(".\\Resourses\\File.txt"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithLinksFollowing, buildValidHierarchyWithSymlinkToFolder)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\SymlinkToFolder");

	std::unique_ptr<FolderNode> expected = std::move(std::make_unique<FolderNode>
		("SymlinkToFolder.symlink -(links to)-> Folder", ".\\Resourses\\Folder",
			fs::file_size(".\\Resourses\\Folder"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithLinksFollowing, buildValidHierarchyWithSymlinkToSymlink)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\SymlinkToSymlink");

	std::unique_ptr<FileNode> expected = std::move(std::make_unique<FileNode>
		("SymlinkToSymlink.symlink -(links to)-> SymlinkToFile.symlink -(links to)-> File.txt", ".\\Resourses\\File.txt",
			fs::file_size(".\\Resourses\\File.txt"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithLinksFollowing, buildValidHierarchyWithFile)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\File.txt");

	std::unique_ptr<FileNode> expected = std::move(std::make_unique<FileNode>
		("File.txt", ".\\Resourses\\File.txt", fs::file_size(".\\Resourses\\File.txt"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithLinksFollowing, buildValidHierarchyWithFolderWithoutSubdirectories)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\Folder");

	std::unique_ptr<FolderNode> expected = std::move(std::make_unique<FolderNode>
		("Folder", ".\\Resourses\\Folder", fs::file_size(".\\Resourses\\Folder"), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithLinksFollowing, buildValidHierarchyWithFolderWithSubdirectoriesWithoutLinks)
{
	BuilderWithLinksFollowing builder;

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

TEST(BuilderWithLinksFollowing, buildValidHierarchyWithFolderWithSubdirectoriesWithLinks)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\FolderWithSubdirectoriesWithLinks");

	std::string localResoursesAbsolutePath1 = fs::absolute(".\\Resourses").string();
	std::unique_ptr<FileNode> subDir1 = std::move(std::make_unique<FileNode>
		("FolderWithSubdirectoriesWithLinks\\Shortcut.lnk -(links to)-> File.txt", localResoursesAbsolutePath1 + "\\File.txt",
			fs::file_size(".\\Resourses\\File.txt"), true));

	std::vector<std::unique_ptr<Directory>> subdirs;
	subdirs.push_back(std::move(subDir1));

	std::unique_ptr<FolderNode> expected = std::move(std::make_unique<FolderNode>
		("FolderWithSubdirectoriesWithLinks", ".\\Resourses\\FolderWithSubdirectoriesWithLinks",
			fs::file_size(".\\Resourses\\FolderWithSubdirectoriesWithLinks"), std::move(subdirs), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithLinksFollowing, buildValidHierarchyWithCycleDependency)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\FolderWithShortcutToItself");

	std::string localResoursesAbsolutePath = fs::absolute(".\\Resourses").string();
	std::unique_ptr<FolderNode> subDir1 = std::move(std::make_unique<FolderNode>
		("FolderWithShortcutToItself\\FolderShortcut.lnk -(links to)-> FolderWithShortcutToItself",
			localResoursesAbsolutePath + "\\FolderWithShortcutToItself", 0, false));

	std::vector<std::unique_ptr<Directory>> subDirs;
	subDirs.push_back(std::move(subDir1));

	std::unique_ptr<FolderNode> expected = std::move(std::make_unique<FolderNode>
		("FolderWithShortcutToItself", ".\\Resourses\\FolderWithShortcutToItself",
			fs::file_size(".\\Resourses\\FolderWithShortcutToItself"), std::move(subDirs)));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithLinksFollowing, buildDirectoryWithErrorStateFileNode)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\unexisting.txt");

	std::unique_ptr<FileNode> expected = std::move(std::make_unique<FileNode>
		("[error reading directory...not able to continue]", ".\\Resourses\\unexisting.txt", 0, false));

	std::unique_ptr<Directory> result = std::move(builder.getResult());
	EXPECT_TRUE(expected->operator==(*result.get()));
}

TEST(BuilderWithLinksFollowing, buildDirectoryWithErrorStateSubDirectories)
{
	BuilderWithLinksFollowing builder;

	builder.build(".\\Resourses\\FolderWithErrorSubDirectory");

	std::string localResoursesAbsolutePath = fs::absolute(".\\Resourses").string();

	std::unique_ptr<FileNode> subDir1 = std::move(std::make_unique<FileNode>
		("FolderWithErrorSubDirectory\\ShortcutToDeletedFile.lnk -(links to)-> [error reading directory...not able to continue]",
			localResoursesAbsolutePath + "\\File2.txt", 0, false));

	std::vector<std::unique_ptr<Directory>> subdirs;
	subdirs.push_back(std::move(subDir1));

	std::unique_ptr<FolderNode> expected = std::move(std::make_unique<FolderNode>
		("FolderWithErrorSubDirectory", ".\\Resourses\\FolderWithErrorSubDirectory",
			0, std::move(subdirs), true));

	std::unique_ptr<Directory> result = std::move(builder.getResult());

	EXPECT_TRUE(expected->operator==(*result.get()));
}

