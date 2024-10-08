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

	speed = 100.f;
	spawnTime = 0.0f;
	bullet = nullptr;
	point = 0;

	alive = true;
	move = true;
}

void Invader::SetInvader(std::string id, InvaderType typeName, float sizeX, float sizeY, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	this->type = typeName;

	std::string texName = "Assets/space_invaders/";

	switch (typeName)
	{
	case OCTOPUS:
		texName += "octopus0.png";
		SetMore(texName, 10);
		SetTexture("Assets/space_invaders/octopus1.png");
		break;

	case CRAB:
		texName += "crab0.png";
		SetMore(texName, 20);
		SetTexture("Assets/space_invaders/crab1.png");
		break;

	case SQUID:
		texName += "squid0.png";
		SetMore(texName, 30);
		SetTexture("Assets/space_invaders/squid1.png");
		break;

	case UFO:
		texName += "ufo.png";
		SetMore(texName, -1);
		break;

	default:
		break;
	}

	if(type != UFO)
		SetTexture("Assets/space_invaders/boom.png");

	SetSize(sizeX, sizeY);
	SetPos(posX, posY);
	SetColor(r, g, b);

	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	c->SetCollision(pos.x, pos.y, size.x, size.y);

	if (type == UFO)
	{
		AudioComponent* a = (AudioComponent*)FindComponent("Audio");
		if (a != nullptr)
		{
			a->SetAudio("Assets/space_invaders/ufo.mp3");
			a->SetPlay(true);
			a->Setloop(true);
		}
	}
	
}

void Invader::SetMore(std::string texName, int points)
{
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	s->SetTexture(texName);

	this->point = points;
}

void Invader::SetSize(float x, float y)
{
	size.x = x;
	size.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetScale({ x, y });

	SetCollider(x, y);
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
	color.r = (unsigned char)r;
	color.g = (unsigned char)g;
	color.b = (unsigned char)b;

	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
		s->SetColor(color);
}

void Invader::SetCollider(float x, float y)
{
	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	c->SetCollision(pos.x, pos.y, x, y);
	//std::cout << "collider : " << c->GetPos().x << ", " << c->GetPos().y << ", " << c->GetSize().x << ", " << c->GetSize().y << std::endl;
}

void Invader::SetTexture(std::string texName)
{
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	s->SetTexture(texName);
}

void Invader::SetTexIndex(int i)
{
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	s->index = i;
}

void Invader::Visible(bool v)
{
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	if (s != nullptr)
	{
		if (v)
		{
			s->SetAlpha(255.f);
			c->SetCollision(pos.x, pos.y, size.x, size.y);
		}
		else
		{
			s->SetAlpha(0.f);
			c->SetCollision(0, 0, 0, 0);
		}
	}
}

void Invader::Dead()
{
	this->alive = false;
	Visible(false);
	SetTexIndex(0);
	//SetSize(0.f, 0.f);
	
	//std::cout << "\"" << this->GetID() << "\"" << " is DEAD" << std::endl;
}

void Invader::Attack()
{
	bullet->alive = true;
	bullet->SetPos(this->pos.x, this->pos.y - (size.y / 2.f));
	bullet->Visible(true);
	bullet->SetSpeed(attackSpeed);
}

int Invader::GetTexIndex() const
{
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	return s->index;
}

void Invader::Sound(bool play)
{
	AudioComponent* a = (AudioComponent*)FindComponent("Audio");
	if (a != nullptr)
	{
		a->SetPlay(!play);
		a->PlayAudio();
	}
}

void Invader::Move(float dt)
{
	float x = this->pos.x - speed * dt;

	SetPos(x, pos.y);
}

void Invader::SetRandomSpawn()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(20.f, 60.f);
	//std::uniform_real_distribution<float> dist(1.f, 10.f);

	this->spawnTime = dist(mt);
}

void Invader::SetAttackTime(float range)
{
	this->attackDt = 0.0f;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(3.f, range);

	this->attackTime = dist(mt);

	//std::cout << "Attack Time : " << attackTime << std::endl;
}

void Invader::SetRandomPoints()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(10, 60);

	this->point = dist(mt) * 5;
}

bool Invader::SetAttack()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 99);

	int n = dist(mt);

	if (n > 49)
		return true;
	else
		return false;
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
