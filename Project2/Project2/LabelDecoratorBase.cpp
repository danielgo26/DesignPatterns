#include "LabelDecoratorBase.h"

LabelDecoratorBase::LabelDecoratorBase(std::unique_ptr<Label> label)
	:label(std::move(label)){}

std::string LabelDecoratorBase::getText() const
{
	return label->getText();
}

std::unique_ptr<Label> LabelDecoratorBase::getLabelWithoutDecorator(const Label& decorator)
{
	return std::move(this->label);
}

const std::unique_ptr<Label>& LabelDecoratorBase::getLabel() const
{
	return this->label;
}

std::unique_ptr<Label> LabelDecoratorBase::removeDecorator(std::unique_ptr<Label> label,
	const Label& decorator)
{
	if (!label)
		throw std::invalid_argument("Invalid label!");
	LabelDecoratorBase* castedLabel = dynamic_cast<LabelDecoratorBase*>(label.get());
	if (castedLabel)
		return std::move(castedLabel->getLabelWithoutDecorator(decorator));
	return std::move(label);
}

bool LabelDecoratorBase::operator==(const Label& other) const
{
	const LabelDecoratorBase* castedOther = dynamic_cast<const LabelDecoratorBase*>(&other);
	if (castedOther && this->label)
		return this->label->operator==(*castedOther->label.get());
	return false;
}

std::string LabelDecoratorBase::toString() const
{
	std::string labelStr;
	if (!this->label)
		labelStr = "[none]";
	else
		labelStr = this->label->toString();
	return "Base Label Decorator for [" + labelStr + "]";
}