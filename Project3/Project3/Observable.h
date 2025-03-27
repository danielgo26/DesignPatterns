#pragma once
#include <vector>
#include <iostream>
#include "Context.h"

class Observer;

class Observable
{
private:
	std::vector<std::weak_ptr<Observer>> observers;
public:
	bool isExpired(int index) const;
	size_t size() const;
	const std::weak_ptr<Observer>& getObserverAt(int index)const;

	virtual void addObserver(const std::shared_ptr<Observer>& observer);
	virtual void removeObserverAt(int index);

	virtual void notify(const Context& context);
	virtual ~Observable() = default;
};