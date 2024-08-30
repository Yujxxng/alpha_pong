#pragma once

#include "../Utils/myUtils.h"

#include "../ComponentManager/GameObject.h"

#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"
#include "../Components/ColliderComponent.h"

#include "../ComponentManager/EventManager.h"

class Score : public GameObject
{
	float size;
	AEVec2 pos;
	Color color;

public:
	~Score();

	void InitScore();
	void SetScore(std::string id, float size, float posX, float posY, float r, float g, float b);
	void SetSize(float s);
	void SetPos(float x, float y);
	void SetColor(float r, float g, float b);

	float GetSize() const { return size; }
	AEVec2 GetPos() const { return pos; }

	void Display();
};