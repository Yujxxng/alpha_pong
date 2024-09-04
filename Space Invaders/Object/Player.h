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
#include "../Object/Life.h"

class Player : public GameObject
{
	AEVec2 size{ 5.f, 5.f };
	AEVec2 pos;
	Color color;

	int lifeNum = 3;
	std::vector<Life*> life;
	Bullet* bullet;
public:
	~Player();

	void InitPlayer();
	void SetPlayer(std::string id, float sizeX, float sizeY, float posX, float posY, float r, float g, float b);
	void SetSize(float x, float y);
	void SetPos(float x, float y);
	void SetColor(float r, float g, float b);
	
	void Sound(bool);

	AEVec2 GetSize() const { return size; }
	AEVec2 GetPos() const { return pos; }
	Bullet* GetBullet() const { return bullet; }

	void Shoot();
	void LoseLife();
	void GetLife();
	
	void printInfo();
};