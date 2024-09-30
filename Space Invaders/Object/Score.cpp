#include "Score.h"

#include <cstdlib>
#include <windows.h>
#include <string>
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

std::string GetUserDir()
{
	char* uservar;
	size_t requiredSize;

	getenv_s(&requiredSize, NULL, 0, "USERPROFILE");
	if (requiredSize == 0)
	{
		std::cout << "USERPROFILE doesn't exist" << std::endl;
		return "";
	}

	uservar = (char*)malloc(requiredSize * sizeof(char));
	if (!uservar)
	{
		std::cout << "Failed to allocate memory" << std::endl;
		return "";
	}
	getenv_s(&requiredSize, uservar, requiredSize, "USERPROFILE");

	std::string dir = uservar;
	free(uservar);

	dir = dir + "\\Documents\\Digipen Invaders\\";

	return dir;
}

void CreateDir(const char* Path)
{
	char DirName[256];
	const char* p = Path;
	char* q = DirName;

	while (*p)
	{
		if (('\\' == *p) || ('/' == *p))
		{
			if (':' != *(p - 1))
			{
				CreateDirectory(DirName, NULL);
			}
		}

		*q++ = *p++;
		*q = '\0';
	}

	CreateDirectory(DirName, NULL);
}

void Score::SaveToJson()
{
	std::string dir = GetUserDir();
	CreateDirectory(dir.c_str(), NULL);

	dir = dir + "data.json";

	std::ofstream jf(dir);

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
	std::string dir = GetUserDir();
	dir = dir + "data.json";

	if (dir.empty())
		return -1;

	std::ifstream jf(dir);

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

