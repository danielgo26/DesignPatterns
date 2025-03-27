#pragma once
#include "LabelImplementation.h"

/// <summary>
/// Factory responsible for label implementation creation
/// The creation proccess takes actions from the user and gives a relevant feedback
/// Returns the created object
/// </summary>

class LabelImplementationFactory
{
public:
	LabelImplementationFactory() = delete;
	static std::unique_ptr<LabelImplementation> create();
};