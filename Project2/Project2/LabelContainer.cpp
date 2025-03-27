#include "LabelContainer.h"

std::vector <std::unique_ptr<Label>> LabelContainer::labels = std::vector<std::unique_ptr<Label>>();

int LabelContainer::size()
{
	return labels.size();
}

std::unique_ptr<Label> LabelContainer::removeLabelAtIndex(size_t index)
{
	if (index <= labels.size()) {
		std::unique_ptr<Label> toRemove = std::move(labels[index]);
		labels.erase(labels.begin() + index);
		return toRemove;
	}
	return nullptr;
}

void LabelContainer::addLabel(std::unique_ptr<Label> toAdd)
{
	if (toAdd)
		labels.push_back(std::move(toAdd));
}

const std::unique_ptr<Label>& LabelContainer::getLabelByIndex(size_t index)
{
	if (index <= labels.size())
		return labels[index];
	return nullptr;
}