#pragma once
#include "../Event/Event.h"

class Entity
{
public:
	virtual void OnEvent(Event* ev) = 0;
};