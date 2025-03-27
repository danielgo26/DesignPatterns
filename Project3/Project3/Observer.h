#pragma once
#include "Context.h"

class Observer
{
public:
	virtual void update(const Context& context) = 0;
	virtual ~Observer() = default;
};