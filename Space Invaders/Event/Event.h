#pragma once
#include <string>

struct Event
{
	Event() {};
	virtual ~Event() {};

	std::string id;
public:
	const std::string getID() const { return id; }
	void SetID(std::string id) { this->id = id; }
};

class Entity
{
public:
	virtual void OnEvent(Event* ev) = 0;
};