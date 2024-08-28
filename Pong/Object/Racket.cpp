#include "Racket.h"

Racket::~Racket()
{
	DeleteComponent("Transform");
	DeleteComponent("Player");
	DeleteComponent("Rigidbody");
	DeleteComponent("Sprite");
}

void Racket::InitRacket()
{
	AddComponent(new TransformComponent(this));
	AddComponent(new PlayerComponent(this));
	AddComponent(new RigidbodyComponent(this));
	AddComponent(new SpriteComponent(this));

	//add controler and more...

}

void Racket::SetRacketID(std::string id)
{
	this->SetID(id);
}

void Racket::SetSize(float x, float y)
{
	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	t->SetScale({ x, y });
}

void Racket::SetPos(float x, float y)
{
	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	t->SetPos({ x, y });
}

void Racket::SetColor(float r, float g, float b)
{
	Color c{ r, g, b };
	
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	s->SetColor(c);
}

void Racket::DrawRacket()
{
	std::cout << "Draw Racket" << std::endl;
}

