#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"

#include "../Object/Player.h"

#include "AEEngine.h"
#include "AEInput.h"

#include <iostream>

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

	Player* p = (Player*)this->GetOwner();
	float dt = AEFrameRateControllerGetFrameTime();
	//Check for input

	if (AEInputCheckCurr(AEVK_LEFT)) r->AddVelocity(-speed, 0);
	if (AEInputCheckCurr(AEVK_RIGHT)) r->AddVelocity(speed, 0);

	if (AEInputCheckCurr(AEVK_SPACE))
	{
		//r->ClearVelocity();
		if (!(p->GetBullet()->alive))
		{
			std::cout << "shh" << std::endl;
			p->Shoot();
		}
	}
	
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
