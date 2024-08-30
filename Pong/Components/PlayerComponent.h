#pragma once
#include "../ComponentManager/LogicComponentManager.h"
#include <unordered_set>

class PlayerComponent : public LogicComponent
{
	std::unordered_set<std::string> keySet;

	float speed = 350.f;
public:
	PlayerComponent(GameObject* owner);

	void Update() override;

	void AddKey(std::string key);
	bool FindKey(std::string key);
	void SetSpeed(float speed);

	void printKey();
	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static ComponentSerializer* CreateComponent(GameObject* owner);
};