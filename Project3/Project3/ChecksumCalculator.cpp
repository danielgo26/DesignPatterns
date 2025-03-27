#include "ChecksumCalculator.h"

ChecksumCalculator::ChecksumCalculator(std::unique_ptr<HashAlgorithmBase> algorithm, size_t partSize)
	:algorithm(std::move(algorithm)), partSize(partSize) {}

const std::unique_ptr<HashAlgorithmBase>& ChecksumCalculator::getHashAlgorithm() const
{
	return this->algorithm;
}

void ChecksumCalculator::changeHashAlgorithm(std::unique_ptr<HashAlgorithmBase> algorithm)
{
	this->algorithm = std::move(algorithm);
}

size_t ChecksumCalculator::getFileSize(std::istream& is) const
{
	if (!is)
		return 0;
	size_t sizeOfFile;
	size_t currPos = is.tellg();
	is.seekg(0, std::ios::end);
	sizeOfFile = is.tellg();
	is.seekg(currPos);

	return sizeOfFile;
}

std::string ChecksumCalculator::getCurrPartsData(std::istream& is, size_t currPartSize)
{
	if (!is)
		return "";

	// Allocate a buffer for the current part
	std::vector<char> buffer(currPartSize + 1);

	// Read the current part into the buffer
	is.read(buffer.data(), currPartSize);

	return (std::string)buffer.data();
}

std::string ChecksumCalculator::calculate(std::istream& is)
{
	if (!is)
		throw std::invalid_argument("Stream could not be opened!");

	//get size
	size_t sizeOfFile = this->getFileSize(is);

	//get file into parts
	std::size_t numParts;
	if (partSize)
		numParts = sizeOfFile / partSize;
	else
		numParts = 0;

	if (sizeOfFile % partSize != 0) {
		++numParts;
	}

	size_t readTillMoment = 0;
	std::string buff;
	this->notify({ "", 0, type::startReadingNewByteGroup });
	// Read the file in parts
	for (std::size_t i = 0; i < numParts; ++i) {
		// Calculate the size of the current part
		std::size_t currentPartSize = std::min(partSize, sizeOfFile - i * partSize);

		std::string currPartContent = this->getCurrPartsData(is, currentPartSize);
		buff.append(currPartContent);

		//notify the observer that a new amount of bytes has been read
		readTillMoment += currentPartSize;
		this->notify({ "", currentPartSize, type::endReadingNewByteGroup });
	}

	if (numParts == 0)
	{
		this->notify({ "", 0, type::endReadingNewByteGroup });
	}

	//use a hash algorithm to get the hash
	std::string a = this->algorithm->getHash(buff);
	return a;
}