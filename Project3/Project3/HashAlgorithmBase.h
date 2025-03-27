#pragma once
#include <iostream>

class HashAlgorithmBase
{
public:
	virtual std::string getHash(std::string str) = 0;
	virtual ~HashAlgorithmBase() = default;
};