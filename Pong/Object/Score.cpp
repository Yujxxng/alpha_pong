#include "Score.h"

Score::~Score()
{
	DeleteComponent("Font");
}

void Score::InitScore()
{
	AddComponent(new Font(this));

	Font* f = (Font*)FindComponent("Font");
	if (f != nullptr)
	{
		f->SetFont("../Assets/liberation-mono.ttf");
	}
}

void Score::SetScore(std::string id, float size, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	SetSize(size);
	SetPos(posX, posY);
	SetColor(r, g, b);
	SetStr();
}

void Score::SetSize(float s)
{
	size = s;
	Font* f = (Font*)FindComponent("Font");
	if (f != nullptr)
		f->SetSize(s);
}

void Score::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;

	Font* f = (Font*)FindComponent("Font");
	if (f != nullptr)
		f->SetPos(x, y);
}

void Score::SetColor(float r, float g, float b)
{
	color.r = r;
	color.g = g;
	color.b = b;

	Font* f = (Font*)FindComponent("Font");
	if (f != nullptr)
		f->SetColor(color);
}

void Score::SetStr()
{
	std::string tmp = to_string(point);

	Font* f = (Font*)FindComponent("Font");
	if (f != nullptr)
	{
		f->SetStr(tmp.c_str());
	}
}

