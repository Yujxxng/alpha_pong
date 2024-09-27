#pragma once

#include "Bullet.h"
#include <vector>
#include <memory>

class BulletManager
{
public:
	int poolSize = 5;
	std::vector<std::unique_ptr<Bullet>> pool;

	void InitBulletManager();
	void DeadBullets();
	
	Bullet* GetBullet();
	int GetAliveBullet();

	void UpdateBullet(float dt);
	float SetAttackTime();

};
