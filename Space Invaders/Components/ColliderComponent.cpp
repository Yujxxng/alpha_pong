#include "ColliderComponent.h"
#include "TransformComponent.h"

bool ColliderComponent::CheckEpsilon(float v, float EP)
{
	if (v < -EP || v > EP)
		return true;

	return false;
}

ColliderComponent::ColliderComponent(GameObject* owner) : EngineComponent(owner)
{
	ID = "Collider";

	pos = { 0, 0 };
	size = { 0, 0 };

	TransformComponent* t = (TransformComponent*)this->GetOwner()->FindComponent("Transform");
	if (t != nullptr)
	{
		pos = t->GetPos();
		size = t->GetScale();
	}
}


void ColliderComponent::SetCollision(float posX, float posY, float sizeX, float sizeY)
{
	pos.x = posX;
	pos.y = posY;
	size.x = sizeX;
	size.y = sizeY;
}

void ColliderComponent::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

bool ColliderComponent::IsCollision(ColliderComponent* other) const
{
	float my_leftX = pos.x - (size.x / 2.f);
	float my_leftY = pos.y + (size.y / 2.f);
	float my_rightX = pos.x + (size.x / 2.f);
	float my_rightY = pos.y - (size.y / 2.f);

	float other_leftX = other->pos.x - (other->size.x / 2.f);
	float other_leftY = other->pos.y + (other->size.y / 2.f);
	float other_rightX = other->pos.x + (other->size.x / 2.f);
	float other_rightY = other->pos.y - (other->size.y / 2.f);


	if (my_leftX > other_rightX || my_rightX < other_leftX ||
		my_leftY < other_rightY || my_rightY > other_leftY)
		return false;
	
	if (my_leftX <= -(W_WIDTH / 2) || my_rightX >= (W_WIDTH / 2)) return true;

	return true;
}

void ColliderComponent::Update()
{
	TransformComponent* t = (TransformComponent*)this->owner->FindComponent("Transform");
	SetPos(t->GetPos().x, t->GetPos().y);

}

void ColliderComponent::LoadFromJson(const json& data)
{
	/*
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
	*/
}

json ColliderComponent::SaveToJson()
{
	json data, componentData;
	data["type"] = "Collider";

	/*
	componentData["velocity"] = { Velocity.x, Velocity.y };
	componentData["maxVelocity"] = { MAXVelocity.x, MAXVelocity.y };
	componentData["drag"] = drag;
	*/

	data["componentData"] = componentData;
	return data;
}

ComponentSerializer* ColliderComponent::CreateComponent(GameObject* owner)
{
	return owner->FindComponent("Collider");
}


