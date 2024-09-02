#include "RigidbodyComponent.h"
#include "TransformComponent.h"

#include "AEEngine.h"
#include "AESystem.h"

bool RigidbodyComponent::CheckEpsilon(float v, float EP)
{
	if (v < -EP || v > EP)
		return true;

	return false;
}

RigidbodyComponent::RigidbodyComponent(GameObject* owner) : EngineComponent(owner), Velocity(), MAXVelocity()
{
	ID = "Rigidbody";
	//EngineComponentManager* mgt = EngineComponentManager::getPtr();
	//mgt->AddEngine(this);

	Velocity.x = 0;
	Velocity.y = 0;
	MAXVelocity.x = 100;
	MAXVelocity.y = 100;
}

void RigidbodyComponent::AddVelocity(const AEVec2& otherVec)
{
	Velocity.x += otherVec.x;
	Velocity.y += otherVec.y;

	Velocity.x = AEClamp(Velocity.x, -MAXVelocity.x, MAXVelocity.x);
	Velocity.y = AEClamp(Velocity.y, -MAXVelocity.y, MAXVelocity.y);
}

void RigidbodyComponent::AddVelocity(float x, float y)
{
	Velocity.x += x;
	Velocity.y += y;

	//Velocity.x = AEClamp(Velocity.x, -MAXVelocity.x, MAXVelocity.x);
	//Velocity.y = AEClamp(Velocity.y, -MAXVelocity.y, MAXVelocity.y);
}

void RigidbodyComponent::ClearVelocity()
{
	Velocity.x = 0;
	Velocity.y = 0;
}

void RigidbodyComponent::Update()
{
	TransformComponent* t = (TransformComponent*)owner->FindComponent("Transform");
	if (!t)
		return;

	float x = t->GetPos().x + Velocity.x * AEFrameRateControllerGetFrameTime(); // + 1.0f + 2 * acc * time * time
	float y = t->GetPos().y + Velocity.y * AEFrameRateControllerGetFrameTime(); // + 1.0f + 2 * acc * time * time

	t->SetPos({ x,y });

	ClearVelocity();

	//If is too low, just set to 0
	if (!CheckEpsilon(Velocity.x))
		Velocity.x = 0;

	if (!CheckEpsilon(Velocity.y))
		Velocity.y = 0;

}

void RigidbodyComponent::LoadFromJson(const json& data)
{
	auto componentData = data.find("componentData");
	if (componentData != data.end())
	{
		auto it = componentData->find("velocity");
		Velocity.x = it->begin().value();
		Velocity.y = (it->begin() + 1).value();

		it = componentData->find("maxVelocity");
		MAXVelocity.x = it->begin().value();
		MAXVelocity.y = (it->begin() + 1).value();

		it = componentData->find("drag");
		drag = it.value();
	}
}

json RigidbodyComponent::SaveToJson()
{
	json data, componentData;
	data["type"] = "Rigidbody";

	componentData["velocity"] = { Velocity.x, Velocity.y };
	componentData["maxVelocity"] = { MAXVelocity.x, MAXVelocity.y };
	componentData["drag"] = drag;

	data["componentData"] = componentData;
	return data;
}

ComponentSerializer* RigidbodyComponent::CreateComponent(GameObject* owner)
{
	return owner->FindComponent("Rigidbody");
}


