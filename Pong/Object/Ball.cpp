#include "Ball.h"
#include <random>
#include <iostream>

Ball::~Ball()
{
	DeleteComponent("Transform");
	//DeleteComponent("Player");
	DeleteComponent("Rigidbody");
	DeleteComponent("Sprite");
	DeleteComponent("Collider");
}

void Ball::InitBall()
{
	AddComponent(new TransformComponent(this));
	//AddComponent(new PlayerComponent(this));
	AddComponent(new RigidbodyComponent(this));
	AddComponent(new SpriteComponent(this));

	//add more...
	AddComponent(new ColliderComponent(this));
}

void Ball::SetBall(std::string id, float sizeX, float sizeY, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	SetSize(sizeX, sizeY);
	SetPos(posX, posY);
	SetColor(r, g, b);

	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	c->SetCollision(pos.x, pos.y, size.x, size.y);
}

void Ball::SetSize(float x, float y)
{
	size.x = x;
	size.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetScale({ x, y });
}

void Ball::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetPos({ x, y });
}

void Ball::SetColor(float r, float g, float b)
{
	color.r = r;
	color.g = g;
	color.b = b;

	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
		s->SetColor(color);
}

void Ball::SetSpeed(float v)
{
	speed = v;

	RigidbodyComponent* r = (RigidbodyComponent*)FindComponent("Rigidbody");
	if (r != nullptr)
		r->SetVelocity(v, v);
}

void Ball::SetAccel(float v)
{
	acceleration = v;

	RigidbodyComponent* r = (RigidbodyComponent*)FindComponent("Rigidbody");
	if (r != nullptr)
		r->SetAccel(v);
}

void Ball::SetDirection()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(-1.f, 1.f);
	std::uniform_real_distribution<float> s(200.f, 500.f);

	//AEVec2 preDir = dir;

	dir.x = dist(mt);
	dir.y = dist(mt);

	//if (dir.x * preDir.x > 0) dir.x = -dir.x;
	if (cp == 0 && dir.y > 0) dir.y = -dir.y;
	if (cp == 1 && dir.y < 0) dir.y = -dir.y;
	if (cp == 2 && dir.x < 0) dir.x = -dir.x;
	if (cp == 3 && dir.x > 0) dir.x = -dir.x;

	speed = s(mt);
	//speed = 2000.f;
	//std::cout << dir.x << " , " << dir.y << std::endl;
}

void Ball::SetPosCenter()
{
	pos.x = 0.f;
	pos.y = 0.f;
	
	SetPos(pos.x, pos.y);

	cp = -1;
	SetDirection();
}

void Ball::Move(float dt)
{
	float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
	dir.x /= len;
	dir.y /= len;

	float x = pos.x + dir.x * (speed * dt);
	float y = pos.y + dir.y * (speed * dt);

	SetPos(x, y);
}

void Ball::Stop()
{
	speed = 0;
}

void Ball::printInfo()
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
