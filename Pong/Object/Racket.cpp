#include "Racket.h"
#include <iostream>
#include "../Components/SpriteComponent.h"

Racket::~Racket()
{
	DeleteComponent("Transform");
	DeleteComponent("Player");
	DeleteComponent("Rigidbody");
	DeleteComponent("Sprite");
	DeleteComponent("Collider");
	DeleteComponent("Audio");
}

void Racket::InitRacket()
{
	AddComponent(new TransformComponent(this));
	AddComponent(new PlayerComponent(this));
	AddComponent(new RigidbodyComponent(this));
	AddComponent(new SpriteComponent(this));
	//add more...
	AddComponent(new ColliderComponent(this));
	AddComponent(new AudioComponent(this));
}

void Racket::SetRacket(std::string id, float sizeX, float sizeY, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	SetSize(sizeX, sizeY);
	SetPos(posX, posY);
	SetColor(r, g, b);

	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	c->SetCollision(pos.x, pos.y, size.x, size.y);

	AudioComponent* a = (AudioComponent*)FindComponent("Audio");
	a->SetAudio("../Assets/pong.mp3");
}

void Racket::SetSize(float x, float y)
{
	size.x = x;
	size.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetScale({ x, y });
}

void Racket::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetPos({ x, y });
}

void Racket::SetColor(float r, float g, float b)
{
	color.r = r;
	color.g = g;
	color.b = b;

	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
		s->SetColor(color);
}

void Racket::Sound(bool play)
{
	AudioComponent* a = (AudioComponent*)FindComponent("Audio");
	if (a != nullptr)
	{
		a->SetPlay(play);
	}
}

void Racket::printInfo()
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
