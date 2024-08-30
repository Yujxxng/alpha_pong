#include "Score.h"

Score::~Score()
{
	DeleteComponent("Transform");
	DeleteComponent("Rigidbody");
	DeleteComponent("Sprite");
}

void Score::InitScore()
{
	AddComponent(new TransformComponent(this));
	AddComponent(new RigidbodyComponent(this));
	AddComponent(new SpriteComponent(this));
}

void Score::SetScore(std::string id, float size, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	SetPos(posX, posY);
	SetColor(r, g, b);
}

void Score::SetSize(float s)
{
	size = s;
}

void Score::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetPos({ x, y });
}

void Score::SetColor(float r, float g, float b)
{
	color.r = r;
	color.g = g;
	color.b = b;

	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
		s->SetColor(color);
}

void Score::Display()
{
}

