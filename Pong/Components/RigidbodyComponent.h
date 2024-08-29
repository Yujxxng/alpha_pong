#pragma once
#include "../ComponentManager/EngineComponentManager.h"

#include "AEMath.h"

class RigidbodyComponent : public EngineComponent
{
	float drag = 1.5f;
	float acceleration = 1.f;

	AEVec2 Velocity;
	AEVec2 MAXVelocity;

	bool CheckEpsilon(float v, float EP = EPSILON);

public:
	RigidbodyComponent(GameObject* owner);

	void SetVelocity(float x, float y);
	void AddVelocity(float x, float y);
	void AddVelocity(const AEVec2& otherVec);

	void ClearVelocity();

	void SetAccel(float a);
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static ComponentSerializer* CreateComponent(GameObject* owner);
};