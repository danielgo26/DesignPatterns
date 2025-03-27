#pragma once
#include <vector>
#include <iostream>
#include "TextTransformation.h"

/// <summary>
/// Heterogene container responsible for text transformations storing and management
/// We use shared_ptr rather than unique_ptr, because of the Flyweight functionality of the
/// CenzoreTransformation - with shared pointers we can use common IMMUTABLE objects, rather than
/// creating new ones with the same behaviour. Practicly, a unique_ptr is much more intuitive and
/// reasonable for the other kinds of text transformations, because we do not share their management
/// to several places - we only manage them from one - that container class here.
/// But for the seek of the application we keep all the transformations within shared_ptr and 
/// having that in mind we have forbidden any functionalities that will make the "shared" objects
/// muttable(in other words, we keep an immutable state for them to deal with that drawback
/// noted above)
/// </summary>

class TextTransformationContainer
{
private:
	static std::vector<std::shared_ptr<TextTransformation>> transformations;
public:
	TextTransformationContainer() = delete;
	static int size();
	static void addTransformation(std::shared_ptr<TextTransformation> toAdd);
	static void removeTransformationAtIndex(size_t index);
	static const std::shared_ptr<TextTransformation>& getTransformationByIndex(size_t index);
};
