#pragma once
#include <list>
#include <string>
#include "../ComponentManager/BaseComponent.h"

//class BaseComponent;

class GameObject
{
	std::string ID;
	std::list<BaseComponent*> components;

public:
	//GameObject();
	~GameObject();

	const std::string GetID() const;
	void SetID(std::string id);

	void AddComponent(BaseComponent* component);
	BaseComponent* FindComponent(std::string cmpID);
	void DeleteComponent(std::string cmpID);
};