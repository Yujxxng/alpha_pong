#include "Invader.h"
#include <iostream>
#include <random>
#include "../Components/SpriteComponent.h"

Invader::~Invader()
{
	DeleteComponent("Transform");
	DeleteComponent("Rigidbody");
	DeleteComponent("Sprite");
	DeleteComponent("Collider");
	DeleteComponent("Audio");
}

void Invader::InitInvader()
{
	AddComponent(new TransformComponent(this));
	AddComponent(new RigidbodyComponent(this));
	AddComponent(new SpriteComponent(this));
	AddComponent(new ColliderComponent(this));
	AddComponent(new AudioComponent(this));
}

void Invader::SetInvader(std::string id, InvaderType type, float sizeX, float sizeY, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	this->type = type;

	std::string texName = "Assets/";

	switch (type)
	{
	case OCTOPUS:
		texName += "Octopus.png";
		SetMore(texName, 10);
		break;

	case CRAB:
		texName += "Crab.png";
		SetMore(texName, 20);
		break;

	case SQUID:
		texName += "Squid.png";
		SetMore(texName, 30);
		break;

	case UFO:
		texName += "UFO.png";
		SetMore(texName, -1);
		break;

	default:
		break;
	}

	SetSize(sizeX, sizeY);
	SetPos(posX, posY);
	SetColor(r, g, b);

	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	c->SetCollision(pos.x, pos.y, size.x, size.y);

	//AudioComponent* a = (AudioComponent*)FindComponent("Audio");
	//a->SetAudio("Assets/pong.mp3");

	//set texture
}

void Invader::SetMore(std::string texName, int point)
{
	//SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	//s->SetTexture(texName);

	this->point = point;
}

void Invader::SetSize(float x, float y)
{
	size.x = x;
	size.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetScale({ x, y });
}

void Invader::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetPos({ x, y });
}

void Invader::SetColor(float r, float g, float b)
{
	color.r = r;
	color.g = g;
	color.b = b;

	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
		s->SetColor(color);
}

void Invader::Sound(bool play)
{
	AudioComponent* a = (AudioComponent*)FindComponent("Audio");
	if (a != nullptr)
	{
		a->SetPlay(play);
	}
}

void Invader::MoveLeft(float dt)
{
	float x = this->pos.x - speed * dt;
	float y = this->pos.y;

	SetPos(x, y);
}

void Invader::MoveRight(float dt)
{
	float x = this->pos.x + speed * dt;
	float y = this->pos.y;

	SetPos(x, y);
}

int Invader::GetRandomPoints()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(50, 300);

	if (this->point < 0)
		return dist(mt);
}

void Invader::printInfo()
{
	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	if (!c)
	{
		std::cout << "NOT FOUND COLLIDER COMPONENT" << std::endl;
		return;
	}
	std::cout << "[" << this->GetID() << " - Collider] POS : " << c->GetPos().x << ", " << c->GetPos().y <<
		" | SIZE : " << c->GetSize().x << ", " << c->GetSize().y << " | POINT : " << this->point << std::endl;
}
