#pragma once
#include "HelpLabel.h"

/// <summary>
/// Class managing the printing with the desired user option(with/without help text)
/// By default the output printing stream is set to the standart output std::cout and
/// the class is storing corresponing user messages for each operation
/// Corresponding selectors and mutators included
/// </summary>

class PrintManager
{
	static std::ostream& printTo;
	static std::string printWithoutHelpMessage;
	static std::string printWithHelpMessage;
public:
	PrintManager() = delete;
	static void setPrintingStream(std::ostream& os);
	static void setPrintingWithoutHelpMessage(const std::string& msg);
	static void setPrintingWithHelpMessage(const std::string& msg);
	static void print(const Label& label);
	static void printWithHelpText(const Label& label);
};