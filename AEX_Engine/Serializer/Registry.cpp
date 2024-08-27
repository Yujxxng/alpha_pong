#include "Registry.h"

#include <iostream>
#include "../Components/AudioComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"

Registry* Registry::registry_ptr = nullptr;

Registry::Registry()
{
	//componentMap.insert({TransformComponent::GetID, &TransformComponent::})
}

ComponentSerializer* Registry::CreateComponent(const std::string& type, GameObject* owner)
{
	if (componentMap.find(type) == componentMap.end())
	{
		std::cerr << "Registry::CreateComponent() Invalid component type " << type << std::endl;
		return nullptr;
	}

	return componentMap[type](owner);
}

Registry* Registry::GetPtr()
{
	if (registry_ptr == nullptr)
	{
		registry_ptr = new Registry;
		return registry_ptr;
	}
	else
		return nullptr;
}

void Registry::DeletePtr()
{
	if (registry_ptr != nullptr)
	{
		delete registry_ptr;
		registry_ptr = nullptr;
	}
}
