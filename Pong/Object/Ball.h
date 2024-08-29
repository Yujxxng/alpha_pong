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

class Ball : public GameObject
{
	AEVec2 size;
	AEVec2 pos;
	Color color;

	float speed;
	float acceleration;

	float direction; //change type

public:
	~Ball();

	void InitBall();
	void SetBall(std::string id, float sizeX, float sizeY, float posX, float posY, float r, float g, float b);
	void SetSize(float x, float y);
	void SetPos(float x, float y);
	void SetColor(float r, float g, float b);
	void SetSpeed(float v);
	void SetAccel(float v);
	void SetDirection(float d);

	AEVec2 GetSize() const { return size; }
	AEVec2 GetPos() const { return pos; }

	void printInfo();
};