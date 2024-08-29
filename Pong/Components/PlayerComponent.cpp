#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"

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
#if 0
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
#elif 1
	if (AEInputCheckCurr(AEVK_SPACE)) //r->ClearVelocity();
		r->SetAccel(5.f);

	if (FindKey("W") && AEInputCheckCurr(AEVK_W))
		r->AddVelocity(0, speed);

	if (FindKey("S") && AEInputCheckCurr(AEVK_S))
		r->AddVelocity(0, -speed);

	if (FindKey("UP") && AEInputCheckCurr(AEVK_UP))
		r->AddVelocity(0, speed);

	if (FindKey("DOWN") && AEInputCheckCurr(AEVK_DOWN))
		r->AddVelocity(0, -speed);
#endif
}

void PlayerComponent::AddKey(std::string key)
{
	keySet.insert(key);
}

bool PlayerComponent::FindKey(std::string key)
{
	if (keySet.find(key) != keySet.end())
		return true;

	return false;
}

void PlayerComponent::SetSpeed(float speed)
{
	this->speed = speed;
}

void PlayerComponent::printKey()
{
	std::cout << this->owner->GetID() << " : ";
	for (auto it = keySet.begin(); it != keySet.end(); it++)
		std::cout << *it << " ";
	std::cout << '\n';
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
