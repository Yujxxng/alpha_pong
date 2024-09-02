#pragma once

#include "../Utils/myUtils.h"

#include "../ComponentManager/GameObject.h"

#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"
#include "../Components/ColliderComponent.h"

enum InvaderType
{
	OCTOPUS,
	CRAB,
	SQUID,
	UFO
};

class Invader : public GameObject
{
	InvaderType type;
	bool alive = true;

	AEVec2 size;
	AEVec2 pos;
	Color color;
	
	float speed = 20.f;

	int point;
	void SetMore(std::string texName, int point);

public:

	~Invader();

	void InitInvader();

	void SetInvader(std::string id, InvaderType type, float sizeX, float sizeY, float posX, float posY, float r, float g, float b);

	void SetSize(float x, float y);
	void SetPos(float x, float y);
	void SetColor(float r, float g, float b);
	void SetSpeed(float v) { speed = v; }

	void Sound(bool);


	AEVec2 GetSize() const { return size; }
	AEVec2 GetPos() const { return pos; }

	void MoveLeft(float dt);
	void MoveRight(float dt);
	int GetRandomPoints();

	void printInfo();
};