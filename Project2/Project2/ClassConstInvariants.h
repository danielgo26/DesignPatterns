#pragma once

namespace
{
	//Indexes for option of a operation in the main menu
	const size_t startOptionIndexMainMenu = 1;
	const size_t endOptionIndexMainMenu = 10;

	//Indexes for with/without help label options
	const size_t startHelpOptionIndexCreate = 1;
	const size_t endHelpOptionIndexCreate = 2;

	//indexes for types of decorators(Text Transformation, Random and Cycling)
	const size_t startTypeDecorationIndex = 1;
	const size_t endTypeDecorationIndex = 3;

	//indexes for types of label implementations(Simple, Rich and Custom)
	const size_t startTypeOfLabelOptionIndex = 1;
	const size_t endTypeOfLabelOptionIndex = 3;

	//indexes for types of text transformations
	const size_t startTextTransformationTypeIndex = 1;
	const size_t endTextTransformationTypeIndex = 8;

	//default empty string replacement
	const std::string notEmptyReplacement = "[empty]";
}
