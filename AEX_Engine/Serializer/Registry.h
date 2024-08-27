#pragma once
#include <string>
#include <map>

class ComponentSerializer;
class GameObject;

class Registry
{
private:
	std::map<std::string, ComponentSerializer* (*)(GameObject* owner)> componentMap;
	Registry(const Registry& other) = delete;
	const Registry& operator= (const Registry& other) = delete;

	static Registry* registry_ptr;

	ComponentSerializer* CreateComponent(const std::string&, GameObject*);
protected:
	Registry() = default;
	~Registry() = default;

public:
	static Registry* GetPtr();
	static void DeletePtr();

	friend class StateSerializer;
};