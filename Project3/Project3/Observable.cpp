#include "Observable.h"
#include "Observer.h"

bool Observable::isExpired(int index) const
{
	if (index >= 0 && index < this->size())
		return this->observers[index].expired();
	return true;
}

size_t Observable::size() const
{
	return this->observers.size();
}

const std::weak_ptr<Observer>& Observable::getObserverAt(int index)const
{
	if (index >= 0 && index < this->size())
		return this->observers[index];
	else
		throw std::invalid_argument("Index out of range!");
}

void Observable::addObserver(const std::shared_ptr<Observer>& observer)
{
	if (observer)
		this->observers.push_back(observer);
}

void Observable::removeObserverAt(int index)
{
	if (index >= 0 && index < this->size())
		this->observers.erase(this->observers.begin() + index);
}

void Observable::notify(const Context& context)
{
	for (size_t i = 0; i < this->size(); i++)
	{
		if (std::shared_ptr<Observer> ptr = this->observers[i].lock())
		{
			ptr->update(context);
		}
	}
}