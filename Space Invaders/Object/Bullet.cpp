#include "Bullet.h"
#include <iostream>
#include <random>
Bullet::~Bullet()
{
	DeleteComponent("Transform");
	DeleteComponent("Rigidbody");
	DeleteComponent("Sprite");
	DeleteComponent("Collider");
}

void Bullet::InitBullet()
{
	AddComponent(new TransformComponent(this));
	AddComponent(new RigidbodyComponent(this));
	AddComponent(new SpriteComponent(this));
	AddComponent(new ColliderComponent(this));
}

void Bullet::SetBullet(std::string id, MissileType type, float sizeX, float sizeY, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	SetType(type);
	SetSize(sizeX, sizeY);
	SetPos(posX, posY);
	SetColor(r, g, b);

	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	c->SetCollision(pos.x, pos.y, size.x, size.y);
}

void Bullet::SetSize(float x, float y)
{
	size.x = x;
	size.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetScale({ x, y });

	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	c->SetCollision(pos.x, pos.y, size.x, size.y);
}

void Bullet::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetPos({ x, y });
}

void Bullet::SetColor(float r, float g, float b)
{
	color.r = r;
	color.g = g;
	color.b = b;

	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
		s->SetColor(color);
}

void Bullet::SetMissileRandom()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 3);
	

	switch (dist(mt))
	{
	case 1:
		SetType(MissileType::SLOW);
		SetColor(255.f, 0.f, 0.f);
		break;
	case 2:
		SetType(MissileType::FAST);
		SetColor(0.f, 255.f, 255.f);
		break;
	case 3:
		SetType(MissileType::WIGGLY);
		SetColor(0.f, 0.f, 255.f);
		break;
	default:
		break;
	}
	SetSpeed(100.f);
}

void Bullet::Visible(bool v)
{
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
	{
		if (v)
			s->SetAlpha(255.f);
		else
			s->SetAlpha(0.f);
	}
}

void Bullet::Fly(float dt)
{
	float y = pos.y + speed * dt * alive;
	SetPos(pos.x, y);
}

void Bullet::FromInvader(float dt)
{
	float y = pos.y - speed * dt * alive;
	SetPos(pos.x, y);
}

void Bullet::Dead()
{
	this->alive = false;
	Visible(false);

	//std::cout << "\"BULLET\"" << " is DEAD" << std::endl;
}

void Bullet::printInfo()
{
	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	if (!c)
	{
		std::cout << "NOT FOUND COLLIDER COMPONENT" << std::endl;
		return;
	}
	std::cout << "[" << this->GetID() << " - Collider] POS : " << c->GetPos().x << ", " << c->GetPos().y <<
		" | SIZE : " << c->GetSize().x << ", " << c->GetSize().y << std::endl;
}
