#pragma once
#include <iostream>

/// <summary>
/// Base abstract class for label implementations (bridge pattern used)
/// Each label implementation should derive from it
/// </summary>

class LabelImplementation
{
public:
	virtual std::string getText() const = 0;
	virtual bool operator==(const LabelImplementation& other) const = 0;
	virtual std::string toString() const = 0;
	virtual ~LabelImplementation() = default;
};	