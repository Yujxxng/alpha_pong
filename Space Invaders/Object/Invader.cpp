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

	std::string texName = "Assets/space_invaders/";

	switch (type)
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

	bullet = new Bullet;
	bullet->InitBullet();
	bullet->SetSize(2.f, 12.f);
	bullet->SetMissileRandom();
	bullet->Dead();

	//AudioComponent* a = (AudioComponent*)FindComponent("Audio");
	//a->SetAudio("Assets/pong.mp3");
}

void Invader::SetMore(std::string texName, int point)
{
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	s->SetTexture(texName);

	this->point = point;
}

void Invader::SetSize(float x, float y)
{
	size.x = x;
	size.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetScale({ x, y });

	SetCollider(0.f, 0.f);
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
}

void Invader::SetTexture(std::string texName)
{
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	s->SetTexture(texName);
}

void Invader::SetTexIndex(int idx)
{
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	s->index = idx;
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
	SetSize(0.f, 0.f);

	//std::cout << "\"" << this->GetID() << "\"" << " is DEAD" << std::endl;
}

void Invader::Attack()
{
	bullet->alive = true;
	bullet->SetPos(this->pos.x, this->pos.y - (size.y / 2.f));
	bullet->Visible(true);
	bullet->SetSpeed(attackSpeed);
}

void Invader::Sound(bool play)
{
	AudioComponent* a = (AudioComponent*)FindComponent("Audio");
	if (a != nullptr)
	{
		a->SetPlay(play);
	}
}

void Invader::Move(float dt)
{
	//float x = this->pos.x - speed * dt * move;
	//float y = this->pos.y;
	float x = this->pos.x - speed * dt;
	float y = this->pos.y;

	//if (this->GetID() != "UFO")
	//{
	//	if (x < -(W_WIDTH / 2) + (this->size.x / 2)) x = -(W_WIDTH / 2) + (this->size.x / 2);
	//	else if (x > (W_WIDTH / 2) - (this->size.x / 2)) x = (W_WIDTH / 2) - (this->size.x / 2);
	//}

	SetPos(x, y);
}

void Invader::SetRandomSpawn()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(20.f, 80.f);
	//std::uniform_real_distribution<float> dist(1.f, 10.f);

	this->spawnTime = dist(mt);
}

void Invader::SetAttackTime(float range)
{
	this->attackDt = 0.0f;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(1.f, range);

	this->attackTime = dist(mt);

	//std::cout << "Attack Time : " << attackTime << std::endl;
}

void Invader::SetRandomPoints()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(50, 300);

	this->point = dist(mt);
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
