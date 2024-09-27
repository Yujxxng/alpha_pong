#pragma once
#include <map>
#include <list>
#include <string>
#include "BaseComponent.h"
#include "LogicComponentManager.h"

using namespace std;

class GameObject
{
	string ID;
	list<BaseComponent*> components;

public:
	//GameObject();
	~GameObject();

	const string GetID() const;
	void SetID(string id);

	void AddComponent(BaseComponent* component);
	BaseComponent* FindComponent(string cmpID);
	BaseComponent* FindComponent(string cmpID) const;
	void DeleteComponent(string cmpID);
};