#pragma once

#include "Bullet.h"
#include <vector>
#include <memory>

class BulletManager
{
public:
	int poolSize = 2;
	std::vector<std::unique_ptr<Bullet>> pool;

	void InitBulletManager();
	Bullet* GetBullet();

	void UpdateBullet(float dt);
	float SetAttackTime();
};
