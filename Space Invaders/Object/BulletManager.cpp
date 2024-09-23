#include "BulletManager.h"
#include <random>

void BulletManager::InitBulletManager()
{
	for (int i = 0; i < poolSize; i++)
		pool.push_back(std::make_unique<Bullet>());

	for (int i = 0; i < poolSize; i++)
	{
		std::string s = "bullet";
		s = s + to_string(i);
		pool[i]->InitBullet(s);
	}
}

void BulletManager::DeleteBullets()
{

}

Bullet* BulletManager::GetBullet()
{
	for (auto& bullet : pool)
	{
		if (!bullet->alive)
			return bullet.get();
	}
	return nullptr;
}

void BulletManager::UpdateBullet(float dt)
{
	for (auto& bullet : pool)
	{
		if (bullet->alive)
		{
			bullet->FromInvader(dt);
			if (bullet->GetPos().y < -(W_HEIGHT / 2.f) || bullet->collision == true)
			{
				bullet->Dead();
			}
		}
	}
}

float BulletManager::SetAttackTime()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(3.f, 6.f);

	return dist(mt);
}

