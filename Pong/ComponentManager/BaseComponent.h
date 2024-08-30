#pragma once
#include <string>
#include "../Serializer/ComponentSerializer.h"


class GameObject;

class BaseComponent : public ComponentSerializer
{
	BaseComponent() = delete;

protected:
	std::string ID;
	GameObject* owner = nullptr;

public:
	BaseComponent(GameObject* owner) : owner(owner) {}
	BaseComponent(const BaseComponent&) = delete;
	BaseComponent& operator=(const BaseComponent&) = delete;

	virtual ~BaseComponent() {}

	std::string GetID() { return this->ID; }

	virtual void Update() = 0;
};
