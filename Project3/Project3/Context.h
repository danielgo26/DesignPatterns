#pragma once
#include <string>

enum class type
{
	startReadingNewByteGroup,
	endReadingNewByteGroup,
	getFileInfo,
	resetInitialState
};

struct Context
{
	std::string fileName;
	size_t bytesProcessed;
	type operationType;
};

