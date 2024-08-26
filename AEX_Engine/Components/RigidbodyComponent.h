#pragma once
#include "../ComponentManager/EngineComponentManager.h"

#include "AEMath.h"

class RigidbodyComponent : public EngineComponent
{
	float drag = 1.5f;
	AEVec2 Velocity;
	AEVec2 MAXVelocity;

	bool CheckEpsilon(float v, float EP = EPSILON);

public:
	RigidbodyComponent(GameObject* owner);

	void AddVelocity(const AEVec2& otherVec);
	void AddVelocity(float x, float y);

	void ClearVelocity();

	void Update() override;
};