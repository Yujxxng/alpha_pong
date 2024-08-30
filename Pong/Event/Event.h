#pragma once
//#include "../Utils/myUtils.h"
#include <string>

struct Event
{
	Event() {};
	virtual ~Event() {};

	std::string id;
public:
	const std::string getID() const { return id; }
};

class Entity
{
public:
	virtual void OnEvent(Event* ev) = 0;
};