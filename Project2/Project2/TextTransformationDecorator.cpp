#include "TextTransformationDecorator.h"

TextTransformationDecorator::TextTransformationDecorator(std::unique_ptr<Label> label,
	std::unique_ptr<TextTransformation> transformation)
	:LabelDecoratorBase(std::move(label))
{
	if (!transformation)
		throw std::invalid_argument("Invalid transformation");
	this->transformation = std::move(transformation);
}

std::string TextTransformationDecorator::getText() const
{
	if (transformation)
		return std::move(transformation->transform(LabelDecoratorBase::getText()));
	return LabelDecoratorBase::getText();
}

std::unique_ptr<Label> TextTransformationDecorator::getLabelWithoutDecorator(const Label& decorator)
{
	if (this->operator==(decorator))
		return std::move(this->label);
	this->label = std::move(LabelDecoratorBase::removeDecorator(std::move(this->label), decorator));
	return std::make_unique<TextTransformationDecorator>(std::move(this->label), std::move(this->transformation));
}

bool TextTransformationDecorator::operator==(const Label& other) const
{
	const TextTransformationDecorator* castedOther = dynamic_cast<const TextTransformationDecorator*>(&other);
	if (castedOther)
		return this->transformation->operator==(*castedOther->transformation.get());
	return false;
}

std::string TextTransformationDecorator::toString() const
{
	std::string labelStr;
	if (!this->label)
		labelStr = "[none]";
	else
		labelStr = this->label->toString();
	return "Text Transformation Label Decorator for [" + labelStr + "]";
}