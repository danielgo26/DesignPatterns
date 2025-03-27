#include "CyclingTransformationDecorator.h"

CyclingTransformationDecorator::CyclingTransformationDecorator(std::unique_ptr<Label> label,
	std::vector<std::unique_ptr<TextTransformation>> transformationsList, size_t startTransformationIndex)
	:LabelDecoratorBase(std::move(label)), indexOfTransformationToBeApplied(startTransformationIndex)
{
	for (size_t i = 0; i < transformationsList.size(); i++)
	{
		if (!transformationsList[i])
			throw std::invalid_argument("Invalid transformation!");
	}
	this->transformationsList = std::move(transformationsList);
}

std::string CyclingTransformationDecorator::getText() const
{
	if (transformationsList.size() > 0)
	{
		if (indexOfTransformationToBeApplied == transformationsList.size())
			indexOfTransformationToBeApplied = 0;
		if (!transformationsList[indexOfTransformationToBeApplied].get())
			return LabelDecoratorBase::getText();

		return std::move(transformationsList[indexOfTransformationToBeApplied++]->transform(LabelDecoratorBase::getText()));
	}
	return LabelDecoratorBase::getText();
}

std::unique_ptr<Label> CyclingTransformationDecorator::getLabelWithoutDecorator(const Label& decorator)
{
	if (this->operator==(decorator))
		return std::move(this->label);
	this->label = LabelDecoratorBase::removeDecorator(std::move(this->label), decorator);
	return std::make_unique<CyclingTransformationDecorator>(std::move(this->label), std::move(this->transformationsList), this->indexOfTransformationToBeApplied);
}

bool CyclingTransformationDecorator::operator==(const Label& other) const
{
	const CyclingTransformationDecorator* castedOther = dynamic_cast<const CyclingTransformationDecorator*>(&other);
	if (castedOther)
	{
		if (this->transformationsList.size() != castedOther->transformationsList.size())
			return false;

		for (size_t i = 0; i < this->transformationsList.size(); i++)
		{
			if (!this->transformationsList[i]->operator==(*castedOther->transformationsList[i].get()))
				return false;
		}
		return true;
	}
	return false;
}

std::string CyclingTransformationDecorator::toString() const
{
	std::string labelStr;
	if (!this->label)
		labelStr = "[none]";
	else
		labelStr = this->label->toString();
	return "Cycling Label Decorator for [" + labelStr + "]";
}