#pragma once

namespace
{
	enum class mainMenuOptions
	{
		CreateLabel = 1,
		CreateTextTransformation = 2,
		DecorateLabel = 3,
		ListAllLabels = 4,
		ListAllTextTransformations = 5,
		DeleteLabel = 6,
		DeleteTextTransformation = 7,
		RemoveDecorator = 8,
		GetLabelContent = 9,
		Exit = 10
	};

	enum class labelImplementations
	{
		simpleLabel = 1,
		richLabel = 2,
		customLabel = 3
	};

	enum class labels
	{
		withHelp = 1,
		withoutHelp = 2
	};

	enum class textTransformations
	{
		capitalize = 1,
		leftTrim = 2,
		rightTrim = 3,
		normalizeSpace = 4,
		decorate = 5,
		cenzor = 6,
		replace = 7,
		composite = 8
	};

	enum class decorators
	{
		textTransformation = 1,
		randomTransformation = 2,
		cyclingTransformation = 3
	};
}