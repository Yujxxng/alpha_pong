#pragma once

#include "../Utils/myUtils.h"

#include "../ComponentManager/GameObject.h"

#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"
#include "../Components/ColliderComponent.h"

#include "../Object/Bullet.h"

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

	AEVec2 size;
	AEVec2 pos;
	Color color;
	
	float speed = 20.f;
	float spawnTime = 0.0f;

	Bullet* bullet;

	int point;
	void SetMore(std::string texName, int point);

public:
	bool alive = true;
	bool move = true;
	bool attack = false;

public:
	~Invader();


	void InitInvader();

	void SetInvader(std::string id, InvaderType type, float sizeX, float sizeY, float posX, float posY, float r, float g, float b);

	void SetSize(float x, float y);
	void SetPos(float x, float y);
	void SetColor(float r, float g, float b);
	void SetSpeed(float v) { speed = v; }
	void SetBullet(Bullet* b) { bullet = b; }
	void Visible(bool);
	void Sound(bool);
	void Dead();
	void Attack();

	AEVec2 GetSize() const { return size; }
	AEVec2 GetPos() const { return pos; }
	Bullet* GetBullet() const { return bullet; }
	float GetSpawnTime() const { return spawnTime; }
	int GetPoints() const { return point; }

	void Move(float dt);
	void SetRandomSpawn();
	void SetRandomPoints();
	void SetAttack();

	void printInfo();
};