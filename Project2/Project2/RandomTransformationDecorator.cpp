#include "RandomTransformationDecorator.h"

RandomTransformationDecorator::RandomTransformationDecorator(std::unique_ptr<Label> label,
	std::vector<std::unique_ptr<TextTransformation>> transformationsList)
	:gen(rd()), LabelDecoratorBase(std::move(label))
{
	for (size_t i = 0; i < transformationsList.size(); i++)
	{
		if (!transformationsList[i])
			throw std::invalid_argument("Invalid transformation!");
	}
	this->transformationsList = std::move(transformationsList);
}

std::string RandomTransformationDecorator::getText() const
{
	if (transformationsList.size() > 0)
	{
		std::uniform_real_distribution<> distrib(0, this->transformationsList.size());
		size_t indexTransformationToBeApplied = distrib(gen);
		if (this->transformationsList[indexTransformationToBeApplied].get())
			return std::move(this->transformationsList[indexTransformationToBeApplied]->transform(LabelDecoratorBase::getText()));
	}
	return LabelDecoratorBase::getText();
}

std::unique_ptr<Label> RandomTransformationDecorator::getLabelWithoutDecorator(const Label& decorator)
{
	if (this->operator==(decorator))
		return std::move(this->label);
	this->label = LabelDecoratorBase::removeDecorator(std::move(this->label), decorator);
	return std::make_unique<RandomTransformationDecorator>(std::move(this->label), std::move(this->transformationsList));
}

bool RandomTransformationDecorator::operator==(const Label& other) const
{
	const RandomTransformationDecorator* castedOther = dynamic_cast<const RandomTransformationDecorator*>(&other);
	if (castedOther)
	{
		if (this->transformationsList.size() != castedOther->transformationsList.size())
			return false;

		for (size_t i = 0; i < this->transformationsList.size(); i++)
		{
			if (!this->transformationsList[i].get()->operator==(*castedOther->transformationsList[i].get()))
				return false;
		}
		return true;
	}
	return false;
}

std::string RandomTransformationDecorator::toString() const
{
	std::string labelStr;
	if (!this->label)
		labelStr = "[none]";
	else
		labelStr = this->label->toString();
	return "Random Label Decorator for [" + labelStr + "]";
}