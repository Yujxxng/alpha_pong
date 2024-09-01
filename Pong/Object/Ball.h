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
	
	float speed{ 1 };
	float acceleration{ 0 };

	AEVec2 dir{ 0, 0 };

	//top 0 bot 1 left 2 right 3
public:
	~Ball();

	int cp = -1;
	void InitBall();

	void SetBall(std::string id, float sizeX, float sizeY, float posX, float posY, float r, float g, float b);
	void SetSize(float x, float y);
	void SetPos(float x, float y);
	void SetColor(float r, float g, float b);
	
	void SetSpeed(float v);
	void SetAccel(float v);
	void SetDirection();
	void SetPosCenter();

	AEVec2 GetSize() const { return size; }
	AEVec2 GetPos() const { return pos; }

	void Move(float dt);
	void Stop();

	void printInfo();
};