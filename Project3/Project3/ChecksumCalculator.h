#pragma once
#include <string>
#include <istream>
#include "Observable.h"
#include "HashAlgorithmBase.h"

class ChecksumCalculator : public Observable
{
private:
	std::unique_ptr<HashAlgorithmBase> algorithm;
	const size_t partSize = 100000;
	size_t getFileSize(std::istream& is) const;
	std::string getCurrPartsData(std::istream& is, size_t currPartSize);
public:
	ChecksumCalculator(std::unique_ptr<HashAlgorithmBase> algorithm, size_t partSize = 100000);

	void changeHashAlgorithm(std::unique_ptr<HashAlgorithmBase> algorithm);
	const std::unique_ptr<HashAlgorithmBase>& getHashAlgorithm() const;
	virtual std::string calculate(std::istream& is);
};