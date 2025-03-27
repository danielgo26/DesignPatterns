#pragma once
#include "LabelDecoratorBase.h"
#include "LabelImplementation.h"

/// <summary>
/// Factory responsible for label creation and decoration
/// Label creation and decoration is achieved with a dependency ingected objects for the corresponding operation
/// Both operations throw when an invalid(nullptr) object is injected
/// Both operations take actions from the user and give a relevant feedback
/// Returns the created object during creation and saves the decorated one in the label container 
/// </summary>

class LabelFactory
{
public:
	LabelFactory() = delete;
	static std::unique_ptr<Label> create(std::unique_ptr<LabelImplementation> impl);
	static void decorate(std::unique_ptr<Label> toDecorate);
};