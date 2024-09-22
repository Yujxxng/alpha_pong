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

enum MissileType
{
	PLAYER = 0,
	SLOW = 1,
	FAST = 2,
	WIGGLY = 3,
};

class Bullet : public GameObject
{
	MissileType missile;

	AEVec2 size;
	AEVec2 pos;
	Color color;

	float speed = 500.f;

public:
	bool alive = false;
	bool collision = false;
public:
	Bullet();
	~Bullet();

	void InitBullet(std::string id);
	void SetBullet(std::string id, MissileType type, float sizeX, float sizeY, float posX, float posY, float r, float g, float b);
	void SetType(MissileType type) { missile = type; }
	void SetSize(float x, float y);
	void SetPos(float x, float y);
	void SetColor(float r, float g, float b);
	void SetSpeed(float v) { speed = v; }
	void SetRandomSpeed();
	void SetMissileRandom();
	void Visible(bool);

	AEVec2 GetSize() const { return size; }
	AEVec2 GetPos() const { return pos; }
	MissileType GetType() const { return missile; }

	void Fly(float dt);
	void FromInvader(float dt);
	void Dead();

	void printInfo();
};