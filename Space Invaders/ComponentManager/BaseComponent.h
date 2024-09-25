#pragma once
#include <string>
#include "..\Serializer\ComponentSerializer.h"
#include <iostream>

using namespace std;

class GameObject;

class BaseComponent : public ComponentSerializer
{
	BaseComponent() = delete;

protected:
	string ID;
	GameObject* owner = nullptr;

public:
	BaseComponent(GameObject* owner) : owner(owner) { std::cout << __FUNCTION__ << std::endl; }
	BaseComponent(const BaseComponent&) = delete;
	BaseComponent& operator=(const BaseComponent&) = delete;

	virtual ~BaseComponent() override { std::cout << __FUNCTION__ << std::endl; }

	string GetID() { return this->ID; }

	virtual void Update() = 0;
};
