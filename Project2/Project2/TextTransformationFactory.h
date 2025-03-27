#pragma once
#include "TextTransformation.h"

/// <summary>
/// Factory responsible for creating text transformations
/// The creation process takes actions from the user and gives a relevant feedback
/// Returns the created object or nullptr if the creation was unsuccessfull
/// </summary>

class TextTransformationFactory
{
public:
	TextTransformationFactory() = delete;
	static std::shared_ptr<TextTransformation> create();
};