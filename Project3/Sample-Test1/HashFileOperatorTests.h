#pragma once
#include <gtest/gtest.h>
#include "..\Project3\FolderNode.h"
#include "..\Project3\FileNode.h"
#include "..\Project3\HashFileOperator.h"
#include "..\Project3\ChecksumCalculator.h"
#include "..\Project3\MD5.h"
#include <sstream>
#include <filesystem>

class MockChecksumCalculator : public ChecksumCalculator {
public:
	MockChecksumCalculator(std::unique_ptr<HashAlgorithmBase> alg)
		:ChecksumCalculator(std::move(alg)) {}

	std::string calculate(std::istream& is) override
	{
		if (!is)
			return "";
		std::string buff, curr;
		while (!is.eof())
		{
			is >> curr;
			buff.append(curr);
			if (!is.eof())
				buff.append(" ");
		}

		return this->getHashAlgorithm()->getHash(buff);
	}
};

TEST(HashFileOperatorTests, operateWithValidDataFromStreamWithLinksFollowing)
{
	FileNode file("relativePath", ".\\Resourses\\ExampleFileReadingText.txt",
		std::filesystem::file_size(".\\Resourses\\ExampleFileReadingText.txt"), true);
	std::unique_ptr<ChecksumCalculator> calc =
		std::make_unique<MockChecksumCalculator>(std::move(std::make_unique<MD5>()));
	HashFileOperator hfo;
	std::stringstream output;
	bool result = hfo.operateWithFileNode(&file, output, std::move(calc));

	std::string expected = "relativePath (hash: 900150983cd24fb0d6963f7d28e17f72)\n";

	EXPECT_EQ(strcmp(output.str().c_str(), expected.c_str()), 0);
	EXPECT_TRUE(result);
}

TEST(HashFileOperatorTests, operateWithValidDataFromStreamWithoutLinksFollowing)
{
	FileNode file("relativePath", ".\\Resourses\\SymlinkToExampleFileReadingText", 0, false);
	std::unique_ptr<ChecksumCalculator> calc =
		std::make_unique<MockChecksumCalculator>(std::move(std::make_unique<MD5>()));
	HashFileOperator hfo;
	std::stringstream output;
	bool result = hfo.operateWithFileNode(&file, output, std::move(calc));

	std::string generatedHash =
		md5(std::filesystem::read_symlink(".\\Resourses\\SymlinkToExampleFileReadingText").string());
	std::string expected = "relativePath (hash: " + generatedHash + ")\n";

	EXPECT_EQ(strcmp(output.str().c_str(), expected.c_str()), 0);
	EXPECT_TRUE(result);
}

TEST(HashFileOperatorTests, operateWithWrongFilePathWithLinksFollowing)
{
	FileNode file("relativePath", ".\\Resourses\\unexisting.txt", 0, true);
	std::unique_ptr<ChecksumCalculator> calc1 =
		std::make_unique<MockChecksumCalculator>(std::move(std::make_unique<MD5>()));
	std::unique_ptr<ChecksumCalculator> calc2 =
		std::make_unique<MockChecksumCalculator>(std::move(std::make_unique<MD5>()));

	HashFileOperator hfo;

	try {
		std::stringstream output;
		hfo.operateWithFileNode(&file, output, std::move(calc1));
		FAIL() << "Expected exception not thrown.";
	}
	catch (const std::runtime_error& e) {

		EXPECT_EQ(strcmp("Could not obtain the file's data!", e.what()), 0);
	}

	bool resultFromGatheringData = hfo.doGatherData(&file, std::move(calc2));

	EXPECT_FALSE(resultFromGatheringData);
}

TEST(HashFileOperatorTests, operateWithWrongFilePathWithoutLinksFollowing)
{
	FileNode file("relativePath", ".\\Resourses\\File.txt", 0, false);
	std::unique_ptr<ChecksumCalculator> calc1 =
		std::make_unique<MockChecksumCalculator>(std::move(std::make_unique<MD5>()));
	std::unique_ptr<ChecksumCalculator> calc2 =
		std::make_unique<MockChecksumCalculator>(std::move(std::make_unique<MD5>()));

	HashFileOperator hfo;

	try {
		std::stringstream output;
		hfo.operateWithFileNode(&file, output, std::move(calc1));
		FAIL() << "Expected exception not thrown.";
	}
	catch (const std::runtime_error& e) {

		EXPECT_EQ(strcmp("Could not obtain the file's data!", e.what()), 0);
	}

	bool resultFromGatheringData = hfo.doGatherData(&file, std::move(calc2));

	EXPECT_FALSE(resultFromGatheringData);
}

TEST(HashFileOperatorTests, operateWithInvalidFile)
{
	std::unique_ptr<ChecksumCalculator> calc1 =
		std::make_unique<MockChecksumCalculator>(std::move(std::make_unique<MD5>()));

	HashFileOperator hfo;

	std::stringstream output;
	bool result = hfo.operateWithFileNode(nullptr, output, std::move(calc1));

	EXPECT_FALSE(result);
}

TEST(HashFileOperatorTests, operateWithInvalidCalculator)
{
	FileNode file("relativePath", ".\\Resourses\\File.txt", 0, false);
	HashFileOperator hfo;

	try {
		std::stringstream output;
		hfo.operateWithFileNode(&file, output, nullptr);
		FAIL() << "Expected exception not thrown.";
	}
	catch (const std::runtime_error& e) {

		EXPECT_EQ(strcmp("Could not obtain the file's data!", e.what()), 0);
	}

	bool result = hfo.doGatherData(&file, nullptr);

	EXPECT_FALSE(result);
}

TEST(HashFileOperatorTests, operateWithInvalidOutputStream)
{
	FileNode file("relativePath", ".\\Resourses\\File.txt", 0, false);
	HashFileOperator hfo;
	std::stringstream output;
	output.setstate(std::ios_base::badbit);

	bool result1 = hfo.operateWithFileNode(&file, output, nullptr);
	bool result2 = hfo.doProcessData(output);

	EXPECT_FALSE(result1);
	EXPECT_FALSE(result2);
}