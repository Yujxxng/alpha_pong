#include "Ball.h"

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
	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	c->SetCollision(pos.x, pos.y, size.x, size.y);
}

void Ball::SetBall(std::string id, float sizeX, float sizeY, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	SetSize(sizeX, sizeY);
	SetPos(posX, posY);
	SetColor(r, g, b);
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
