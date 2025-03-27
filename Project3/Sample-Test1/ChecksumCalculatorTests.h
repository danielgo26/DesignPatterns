#pragma once
#include "gtest/gtest.h"
#include "..\Project3\ChecksumCalculator.h"
#include "..\Project3\HashAlgorithmBase.h"
#include "..\Project3\MD5.h"
#include "..\Project3\SHA256.h"
#include "..\Project3\Observer.h"
#include <stdexcept>
#include <sstream>

class MockHashAlgorithm : public HashAlgorithmBase {
public:
	MockHashAlgorithm() = default;
	std::string getHash(std::string str) override
	{
		return str;
	}
};

class MockObserver : public Observer
{
public:
	MockObserver() = default;
	std::vector<Context> contexts;
	void update(const Context& context) override
	{
		contexts.push_back(context);
	}
};

TEST(ChecksumCalculatorTest, calculateValidHashForFileWithOnePartition)
{
	ChecksumCalculator calc(std::make_unique<MockHashAlgorithm>());

	std::stringstream ss("Some file");
	EXPECT_EQ(strcmp(calc.calculate(ss).c_str(), "Some file"), 0);
}

TEST(ChecksumCalculatorTest, calculateValidHashForFileWithTwoPartitions)
{
	ChecksumCalculator calc(std::make_unique<MockHashAlgorithm>(), 5);

	std::stringstream ss("myFiles");
	EXPECT_EQ(strcmp(calc.calculate(ss).c_str(), "myFiles"), 0);
}

TEST(ChecksumCalculatorTest, calculateValidHashForFileUsingMD5)
{
	ChecksumCalculator calc(std::make_unique<MD5>());

	std::stringstream ss("abc");
	EXPECT_EQ(strcmp(calc.calculate(ss).c_str(), "900150983cd24fb0d6963f7d28e17f72"), 0);


	ss.str("Hello world!");
	EXPECT_EQ(strcmp(calc.calculate(ss).c_str(), "86fb269d190d2c85f6e0468ceca42a20"), 0);
}

TEST(ChecksumCalculatorTest, calculateValidHashForFileUsingSAH256)
{
	ChecksumCalculator calc(std::make_unique<SHA256>());

	std::stringstream ss("abc");
	EXPECT_EQ(strcmp(calc.calculate(ss).c_str(), "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"), 0);


	ss.str("Hello world!");
	EXPECT_EQ(strcmp(calc.calculate(ss).c_str(), "c0535e4be2b79ffd93291305436bf889314e4a3faec05ecffcbb7df31ad9e51a"), 0);
}

TEST(ChecksumCalculatorTest, calculateValidHashWhenHashAlgorithmsChange)
{
	ChecksumCalculator calc(std::make_unique<MD5>());

	std::stringstream ss("abc");
	EXPECT_EQ(strcmp(calc.calculate(ss).c_str(), "900150983cd24fb0d6963f7d28e17f72"), 0);

	ss.str("abc");
	calc.changeHashAlgorithm(std::make_unique<SHA256>());
	EXPECT_EQ(strcmp(calc.calculate(ss).c_str(), "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"), 0);

	ss.str("abc");
	calc.changeHashAlgorithm(std::make_unique<MD5>());
	EXPECT_EQ(strcmp(calc.calculate(ss).c_str(), "900150983cd24fb0d6963f7d28e17f72"), 0);
}

TEST(ChecksumCalculatorTest, calculateValidHashWhenFileHasZeroSize)
{
	ChecksumCalculator calc(std::make_unique<SHA256>());

	std::stringstream ss("");
	EXPECT_EQ(strcmp(calc.calculate(ss).c_str(), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"), 0);
}

TEST(ChecksumCalculatorTest, notifyWhileCalculatingHashes)
{
	std::shared_ptr<MockObserver> obs = std::make_shared<MockObserver>();
	ChecksumCalculator calc(std::make_unique<MD5>());
	calc.addObserver(obs);

	std::stringstream ss("abc");
	calc.calculate(ss);

	EXPECT_EQ(obs->contexts.size(), 2);

	//first notify
	EXPECT_EQ(strcmp(obs->contexts[0].fileName.c_str(), ""), 0);
	EXPECT_EQ(obs->contexts[0].bytesProcessed, 0);
	EXPECT_EQ(obs->contexts[0].operationType, type::startReadingNewByteGroup);

	//second notify
	EXPECT_EQ(strcmp(obs->contexts[1].fileName.c_str(), ""), 0);
	EXPECT_EQ(obs->contexts[1].bytesProcessed, 3);
	EXPECT_EQ(obs->contexts[1].operationType, type::endReadingNewByteGroup);
}

TEST(ChecksumCalculatorTest, notifyWhileCalculatingHashesWithFileWithSizeZero)
{
	std::shared_ptr<MockObserver> obs = std::make_shared<MockObserver>();
	ChecksumCalculator calc(std::make_unique<MD5>());
	calc.addObserver(obs);

	std::stringstream ss("");
	calc.calculate(ss);

	EXPECT_EQ(obs->contexts.size(), 2);

	//first notify
	EXPECT_EQ(strcmp(obs->contexts[0].fileName.c_str(), ""), 0);
	EXPECT_EQ(obs->contexts[0].bytesProcessed, 0);
	EXPECT_EQ(obs->contexts[0].operationType, type::startReadingNewByteGroup);

	//second notify
	EXPECT_EQ(strcmp(obs->contexts[1].fileName.c_str(), ""), 0);
	EXPECT_EQ(obs->contexts[1].bytesProcessed, 0);
	EXPECT_EQ(obs->contexts[1].operationType, type::endReadingNewByteGroup);
}