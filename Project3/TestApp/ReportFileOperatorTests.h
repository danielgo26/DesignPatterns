#pragma once
#include <gtest/gtest.h>
#include "..\Project3\FolderNode.h"
#include "..\Project3\FileNode.h"
#include "..\Project3\ReportFileOperator.h"
#include <sstream>
#include <filesystem>
#include <string>

TEST(ReportFileOperatorTests, operateWithValidDataFromStream)
{
	size_t bytesSize = std::filesystem::file_size(".\\Resourses\\ExampleFileReadingText.txt");
	FileNode file("relativePath", ".\\Resourses\\ExampleFileReadingText.txt", bytesSize, true);
	ReportFileOperator rfo;
	std::stringstream output;
	bool result = rfo.operateWithFileNode(&file, output);

	std::string expected = "relativePath (" + std::to_string(bytesSize) + " bytes)\n";

	EXPECT_EQ(strcmp(output.str().c_str(), expected.c_str()), 0);
	EXPECT_TRUE(result);
}

TEST(ReportFileOperatorTests, operateWithInvalidFile)
{
	ReportFileOperator rfo;

	std::stringstream output;
	bool result1 = rfo.doGatherData(nullptr);
	bool result2 = rfo.operateWithFileNode(nullptr, output);

	EXPECT_FALSE(result1);
	EXPECT_FALSE(result2);
}

TEST(ReportFileOperatorTests, operateWithInvalidOutputStream)
{
	FileNode file("relativePath", ".\\Resourses\\File.txt", 0, false);
	ReportFileOperator rfo;
	std::stringstream output;
	output.setstate(std::ios_base::badbit);

	bool result1 = rfo.operateWithFileNode(&file, output);
	bool result2 = rfo.doProcessData(output);

	EXPECT_FALSE(result1);
	EXPECT_FALSE(result2);
}