#include "Player.h"
#include <iostream>
#include "../Components/SpriteComponent.h"

Player::~Player()
{
	DeleteComponent("Transform");
	DeleteComponent("Player");
	DeleteComponent("Rigidbody");
	DeleteComponent("Sprite");
	DeleteComponent("Collider");
	DeleteComponent("Audio");

	delete bullet;
}

void Player::InitPlayer()
{
	AddComponent(new TransformComponent(this));
	AddComponent(new PlayerComponent(this));
	AddComponent(new RigidbodyComponent(this));
	AddComponent(new SpriteComponent(this));
	AddComponent(new ColliderComponent(this));
	AddComponent(new AudioComponent(this));
}

void Player::SetPlayer(std::string id, float sizeX, float sizeY, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	SetSize(sizeX, sizeY);
	SetPos(posX, posY);
	SetColor(r, g, b);

	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	c->SetCollision(pos.x, pos.y, size.x, size.y);

	bullet = new Bullet;
	bullet->InitBullet();
	bullet->SetType(MissileType::PLAYER);
	bullet->SetSize(2.f, 4.f);

	//AudioComponent* a = (AudioComponent*)FindComponent("Audio");
	//a->SetAudio("Assets/pong.mp3");
}

void Player::SetSize(float x, float y)
{
	size.x = x;
	size.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetScale({ x, y });
}

void Player::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetPos({ x, y });
}

void Player::SetColor(float r, float g, float b)
{
	color.r = r;
	color.g = g;
	color.b = b;

	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
		s->SetColor(color);
}

void Player::Sound(bool play)
{
	AudioComponent* a = (AudioComponent*)FindComponent("Audio");
	if (a != nullptr)
	{
		a->SetPlay(play);
	}
}

void Player::Shoot()
{
	bullet->alive = true;
	bullet->SetPos(this->pos.x, this->pos.y + (size.y / 2.f));
	bullet->SetColor(255.f, 0.f, 0.f);
	bullet->Visible(true);
}

void Player::printInfo()
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
