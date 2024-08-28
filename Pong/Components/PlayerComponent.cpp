#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"

#include "AEEngine.h"
#include "AEInput.h"

PlayerComponent::PlayerComponent(GameObject* owner) : LogicComponent(owner)
{
	ID = "Player";
}

void PlayerComponent::Update()
{
	TransformComponent* t = (TransformComponent*)owner->FindComponent("Transform");
	if (!t)
		return;
	
	RigidbodyComponent* r = (RigidbodyComponent*)owner->FindComponent("Rigidbody");
	if (!r)
		return;

	//Check for input
	if (AEInputCheckCurr(AEVK_W))
	{
		//Move my transform up
		r->AddVelocity(0, speed);
	}

	if (AEInputCheckCurr(AEVK_S)) r->AddVelocity(0, -speed);
	if (AEInputCheckCurr(AEVK_A)) r->AddVelocity(-speed, 0);
	if (AEInputCheckCurr(AEVK_D)) r->AddVelocity(speed, 0);

	if (AEInputCheckCurr(AEVK_SPACE)) r->ClearVelocity();
	if (AEInputCheckCurr(AEVK_Q)) t->SetRot({ t->GetRot() - 0.5f });
	if (AEInputCheckCurr(AEVK_E)) t->SetRot({ t->GetRot() + 0.5f });
}

void PlayerComponent::SetSpeed(float speed)
{
	this->speed = speed;
}

void PlayerComponent::LoadFromJson(const json& data)
{
	auto componentData = data.find("componentData");
	if (componentData != data.end())
	{
		auto it = componentData->find("speed");
		speed = it->begin().value();
	}
}

json PlayerComponent::SaveToJson()
{
	json data, componentData;
	data["type"] = "Player";

	componentData["speed"] = speed;
	data["componentData"] = componentData;

	return data;
}

ComponentSerializer* PlayerComponent::CreateComponent(GameObject* owner)
{
	return owner->FindComponent("Player");
}
