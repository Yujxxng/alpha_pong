#include "Life.h"
#include <iostream>
#include "../Components/SpriteComponent.h"

Life::~Life()
{
	DeleteComponent("Transform");
	DeleteComponent("Sprite");
}

void Life::InitLife()
{
	AddComponent(new TransformComponent(this));
	AddComponent(new SpriteComponent(this));
	SetSize(this->size.x, this->size.y);
}

void Life::SetLife(std::string id, float sizeX, float sizeY, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	SetSize(sizeX, sizeY);
	SetPos(posX, posY);
	SetColor(r, g, b);
}

void Life::SetSize(float x, float y)
{
	size.x = x;
	size.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetScale({ x, y });
}

void Life::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;

	TransformComponent* t = (TransformComponent*)FindComponent("Transform");
	if(t != nullptr)
		t->SetPos({ x, y });
}

void Life::SetColor(float r, float g, float b)
{
	color.r = r;
	color.g = g;
	color.b = b;

	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
		s->SetColor(color);
}

void Life::SetTexture(std::string texName)
{
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
		s->SetTexture(texName);
}

void Life::Visible(bool visible)
{
	SpriteComponent* s = (SpriteComponent*)FindComponent("Sprite");
	if (s != nullptr)
	{
		if (visible)
			s->SetAlpha(255.f);
		else
			s->SetAlpha(0.f);
	}
}
