#include "GameObject.h"

GameObject::~GameObject()
{
	for (auto it = components.begin(); it != components.end(); it++)
	{
		delete* it;
	}

	components.clear();

	//delete this;
}

const string GameObject::GetID() const
{
	return this->ID;
}

void GameObject::SetID(string id)
{
	this->ID = id;
}

void GameObject::AddComponent(BaseComponent* component)
{
	this->components.push_back(component);
}

BaseComponent* GameObject::FindComponent(string cmpID)
{
	if (components.empty()) return nullptr;

	for (auto it = components.begin(); it != components.end(); it++)
	{
		if ((*it)->GetID() == cmpID)
			return (*it);
	}
	return nullptr;
}

BaseComponent* GameObject::FindComponent(string cmpID) const
{
	return const_cast<GameObject*>(this)->FindComponent(cmpID);
}

void GameObject::DeleteComponent(string cmpID)
{
	BaseComponent* tmp = FindComponent(cmpID);
	components.remove(tmp);

	if(tmp)
		delete tmp;
}