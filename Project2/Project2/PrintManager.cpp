#include "PrintManager.h"
#include "LabelDecoratorBase.h"

std::ostream& PrintManager::printTo = std::cout;
std::string PrintManager::printWithoutHelpMessage = "Label\'s content: ";
std::string PrintManager::printWithHelpMessage = "Some help info about the label: ";

void PrintManager::print(const Label& label)
{
	printTo << printWithoutHelpMessage << label.getText() << std::endl;
}

namespace
{
	void printHelpTextIfAny(const Label& label, std::ostream& printTo, const std::string& helpMsg)
	{
		const HelpLabel* castedLabel = dynamic_cast<const HelpLabel*>(&label);
		if (castedLabel) {
			printTo << helpMsg << castedLabel->getHelpText() << std::endl;
		}
		else
		{
			const LabelDecoratorBase* castedToDecorator = dynamic_cast<const LabelDecoratorBase*>(&label);
			if (castedToDecorator)
			{
				printHelpTextIfAny(*castedToDecorator->getLabel(), printTo, helpMsg);
			}
			else {
				printTo << "No help text provided for that label!" << std::endl;
			}
		}
	}
}

void PrintManager::printWithHelpText(const Label& label)
{
	print(label);
	printHelpTextIfAny(label, printTo, printWithHelpMessage);
}

void PrintManager::setPrintingStream(std::ostream& os)
{
	printTo.rdbuf(os.rdbuf());
}
void PrintManager::setPrintingWithoutHelpMessage(const std::string& msg)
{
	printWithoutHelpMessage = msg;
}

void PrintManager::setPrintingWithHelpMessage(const std::string& msg)
{
	printWithHelpMessage = msg;
}