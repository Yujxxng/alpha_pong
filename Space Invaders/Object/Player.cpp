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
	for (int i = 0; i < life.size(); i++)
		delete life[i];
}

void Player::InitPlayer()
{
	AddComponent(new TransformComponent(this));
	AddComponent(new PlayerComponent(this));
	AddComponent(new RigidbodyComponent(this));
	AddComponent(new SpriteComponent(this));
	AddComponent(new ColliderComponent(this));
	AddComponent(new AudioComponent(this));

	for (int i = 0; i < lifeNum - 1; i++)
	{
		life.push_back(new Life);
		life[i]->InitLife();
		life[i]->SetColor(0.f, 255.f, 0.f);
		life[i]->SetPos((W_WIDTH / 2) - 50.f + (30.f * i), (W_HEIGHT / 2) - 20.f);
	}

}

void Player::SetPlayer(std::string id, float sizeX, float sizeY, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	SetSize(sizeX, sizeY);
	SetPos(posX, posY);
	SetColor(r, g, b);

	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	c->SetCollision(pos.x, pos.y, size.x, size.y);

	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	s->SetTexture("Assets/space_invaders/player.png");

	bullet = new Bullet;
	bullet->SetType(MissileType::PLAYER);
	bullet->SetSize(2.f, 6.f);
	bullet->SetColor(0.f, 255.f, 0.f);
	bullet->Visible(false);

	AudioComponent* a = (AudioComponent*)FindComponent("Audio");
	a->SetAudio("Assets/space_invaders/shoot.mp3");
	a->SetPlay(true);
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
	color.r = (unsigned char)r;
	color.g = (unsigned char)g;
	color.b = (unsigned char)b;

	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
		s->SetColor(color);
}

void Player::SetCollider(float x, float y)
{
	ColliderComponent* c = (ColliderComponent*)FindComponent("Collider");
	c->SetCollision(pos.x, pos.y, x, y);
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
	AudioComponent* a = (AudioComponent*)FindComponent("Audio");
	a->SetPlay(false);
}

void Player::LoseLife()
{
	if (lifeNum < 2)
	{
		lifeNum = 0;
		return;
	}

	life[lifeNum-2]->Visible(false);
	lifeNum--;

	//alive = false;
	//set sprite
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
