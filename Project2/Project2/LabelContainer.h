#pragma once
#include <vector>
#include "Label.h"

/// <summary>
/// Heterogene container responsible for label(both plain and decorated ones)storing and management
/// </summary>

class LabelContainer
{
private:
	static std::vector <std::unique_ptr<Label>> labels;
public:
	LabelContainer() = delete;
	static int size();
	static void addLabel(std::unique_ptr<Label> toAdd);
	static std::unique_ptr<Label> removeLabelAtIndex(size_t index);
	static const std::unique_ptr<Label>& getLabelByIndex(size_t index);
};