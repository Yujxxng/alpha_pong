#include "Score.h"

#include <iostream>
#include <fstream>

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
		f->SetFont("Assets/space_invaders.ttf");
	}
}

void Score::SetScore(std::string id, float sz, float posX, float posY, float r, float g, float b)
{
	this->SetID(id);
	SetSize(sz);
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
	color.r = (unsigned char)r;
	color.g = (unsigned char)g;
	color.b = (unsigned char)b;

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

void Score::SaveToJson()
{
	std::ofstream jf("data.json");

	if (!jf.is_open())
	{
		std::cout << "FILE NOT FOUND" << std::endl;
		return;
	}
	using json = nlohmann::json;
	json data;
	data["High Score"] = point;

	std::string tmp = data.dump(-1);
	jf.write(tmp.c_str(), tmp.size());

	jf.close();
}

int Score::LoadFromJson()
{
	std::ifstream jf("data.json");

	if (!jf.is_open())
	{
		std::cout << "FILE NOT FOUND" << std::endl;
		return -1;
	}
	using json = nlohmann::json;
	json data;
	jf >> data;

	int score = 0;
	auto ch = data.find("High Score");
	if (ch != data.end())
	{
		score = data.at("High Score").get<int>();
	}

	jf.close();

	return score;
}

