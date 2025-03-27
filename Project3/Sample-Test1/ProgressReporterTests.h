#pragma once
#include <gtest/gtest.h>
#include "..\Project3\ProgressReporter.h"
#include <sstream>

class MockProgressReporter : public ProgressReporter
{
public:
	MockProgressReporter(size_t bytesToRead, std::ostream& displayProgressStream = std::cout)
		:ProgressReporter(bytesToRead, displayProgressStream) {}

	std::string getCurrOperatingFilePath() const
	{
		return this->currOperatingFilePath;
	}
	long long getTotalBytesToRead() const
	{
		return this->totalBytesToRead;
	}
	long long getBytesProcessedByLastTick() const
	{
		return this->bytesProcessedByLastTick;
	}
	long long getTotalBytesProcessedByFar() const
	{
		return this->totalBytesProcessedByFar;
	}
	double getCurrAverageSpeed() const
	{
		return this->currAverageSpeed;
	}
	std::chrono::steady_clock::time_point getCurrStartTime() const
	{
		return this->currStartTime;
	}
	bool getNoStartTime() const
	{
		return this->noStartTime;
	}
	long long getElapsed_time() const
	{
		return this->elapsed_time;
	}
	long long getCurrTimeRemaining()const
	{
		return this->currTimeRemaining;
	}
};

TEST(ProgressReporterTests, constructorCreatesValidObjects)
{
	MockProgressReporter reporter(100);
	EXPECT_EQ(reporter.getTotalBytesToReadCount(), 100);

	reporter.setTotalBytesToReadCount(200);
	EXPECT_EQ(reporter.getTotalBytesToReadCount(), 200);
}

TEST(ProgressReporterTests, updateWithGetFileInfoState)
{
	std::stringstream ss;
	int countOfBytes = 100;
	MockProgressReporter reporter(countOfBytes, ss);
	Context ctx = { "New file.txt", 0, type::getFileInfo };

	reporter.update(ctx);

	EXPECT_EQ(strcmp(reporter.getCurrOperatingFilePath().c_str(), "New file.txt"), 0);
	EXPECT_TRUE(reporter.getCurrStartTime().time_since_epoch().count() == 0);
}

TEST(ProgressReporterTests, startReadingNewByteGroupFromInitialProgressBarState)
{
	std::stringstream ss;
	int countOfBytes = 50;
	MockProgressReporter reporter(countOfBytes, ss);
	Context sendFileName = { "New file.txt", 0, type::getFileInfo };
	Context startFirstByteGroup = { "", 0, type::startReadingNewByteGroup };

	reporter.update(sendFileName);
	ss.str("");
	reporter.update(startFirstByteGroup);

	std::string expected = "[..................................................] "
		"0.000%\r\nProccessing: New file.txt...";

	EXPECT_EQ(strcmp(ss.str().c_str(), expected.c_str()), 0);
	EXPECT_TRUE(reporter.getCurrStartTime().time_since_epoch().count() > 0);
}

TEST(ProgressReporterTests, startReadingNewByteGroupFromIntermediateProgressBarStateSameFile)
{
	std::stringstream ss, output;
	int countOfBytes = 100;
	int bytesProceeded = 22;
	MockProgressReporter reporter(countOfBytes, ss);
	Context sendFileName = { "New file.txt", 0, type::getFileInfo };
	Context startFirstByteGroup = { "", 0, type::startReadingNewByteGroup };
	Context process22Bytes = { "", bytesProceeded, type::endReadingNewByteGroup };
	Context startAnotherGroup = { "", 0, type::startReadingNewByteGroup };

	reporter.update(sendFileName);
	reporter.update(startFirstByteGroup);
	ss.str("");
	reporter.update(process22Bytes);

	std::string ms = std::to_string(reporter.getCurrTimeRemaining());
	std::string byteProceededStr = std::to_string(bytesProceeded);

	std::string expected = "[///////////.......................................] "
		+ byteProceededStr +
		".000%\r\nProccessing: "
		+ reporter.getCurrOperatingFilePath() +
		"...  22 bytes processed so far( "
		+ ms +
		" ms remaining...)\n";

	EXPECT_EQ(strcmp(ss.str().c_str(), expected.c_str()), 0);
}

TEST(ProgressReporterTests, startReadingNewByteGroupFromIntermediateProgressBarStateAnotherFile)
{
	std::stringstream ss, output;
	int countOfBytes = 100;
	int bytesProceeded = 68;
	MockProgressReporter reporter(countOfBytes, ss);
	Context sendFileName = { "New file.txt", 0, type::getFileInfo };
	Context startFirstByteGroup = { "", 0, type::startReadingNewByteGroup };
	Context process22Bytes = { "", 22, type::endReadingNewByteGroup };
	Context sendAnotherFileName = { "Another file.txt", 0, type::getFileInfo };
	Context startAnotherGroup = { "", 0, type::startReadingNewByteGroup };
	Context process46Bytes = { "", 46, type::endReadingNewByteGroup };

	reporter.update(sendFileName);
	reporter.update(startFirstByteGroup);
	reporter.update(process22Bytes);
	reporter.update(sendAnotherFileName);
	reporter.update(startAnotherGroup);
	ss.str("");
	reporter.update(process46Bytes);

	std::string ms = std::to_string(reporter.getCurrTimeRemaining());
	std::string byteProceededStr = std::to_string(bytesProceeded);

	std::string expected = "[//////////////////////////////////................] "
		+ byteProceededStr +
		".000%\r\nProccessing: "
		+ reporter.getCurrOperatingFilePath() +
		"...  46 bytes processed so far( "
		+ ms +
		" ms remaining...)\n";

	EXPECT_EQ(strcmp(ss.str().c_str(), expected.c_str()), 0);
}

TEST(ProgressReporterTests, startReadingNewByteGroupFromFinalProgressBarStateAnotherFile)
{
	std::stringstream ss, output;
	int countOfBytes = 100;
	int bytesProceeded = 100;
	MockProgressReporter reporter(countOfBytes, ss);
	Context sendFileName = { "New file.txt", 0, type::getFileInfo };
	Context startFirstByteGroup = { "", 0, type::startReadingNewByteGroup };
	Context process36Bytes = { "", 36, type::endReadingNewByteGroup };
	Context sendAnotherFileName = { "Another file.txt", 0, type::getFileInfo };
	Context startAnotherGroup = { "", 0, type::startReadingNewByteGroup };
	Context process64Bytes = { "", 64, type::endReadingNewByteGroup };

	reporter.update(sendFileName);
	reporter.update(startFirstByteGroup);
	reporter.update(process36Bytes);
	reporter.update(sendAnotherFileName);
	reporter.update(startAnotherGroup);
	ss.str("");
	reporter.update(process64Bytes);

	std::string ms = std::to_string(reporter.getCurrTimeRemaining());
	std::string byteProceededStr = std::to_string(bytesProceeded);

	std::string expected = "[//////////////////////////////////////////////////] "
		+ byteProceededStr +
		".000%\r\nProccessing: "
		+ reporter.getCurrOperatingFilePath() +
		"...  64 bytes processed so far( "
		+ ms +
		" ms remaining...)\n";

	EXPECT_EQ(strcmp(ss.str().c_str(), expected.c_str()), 0);
}

TEST(ProgressReporterTests, updateWithResetInitialState)
{
	std::stringstream ss;
	MockProgressReporter reporter(100, ss);
	Context ctx = { "New file.txt", 0, type::resetInitialState };
	reporter.update(ctx);

	EXPECT_EQ(strcmp(reporter.getCurrOperatingFilePath().c_str(), ""), 0);
	EXPECT_EQ(reporter.getBytesProcessedByLastTick(), 0);
	EXPECT_EQ(reporter.getTotalBytesProcessedByFar(), 0);
	EXPECT_EQ(reporter.getCurrAverageSpeed(), -1);
	EXPECT_EQ(reporter.getNoStartTime(), true);
	EXPECT_EQ(reporter.getElapsed_time(), 0);
}

TEST(ProgressReporterTests, updateWithUnknownState)
{
	std::stringstream ss;
	MockProgressReporter reporter(100, ss);
	Context ctx = { "New file.txt", 0, (type)100 };
	reporter.update(ctx);

	EXPECT_EQ(strcmp(ss.str().c_str(), "Unknown message..."), 0);
}
