#include "Score.h"

#include <cstdlib>
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>

Score* Score::score_ptr = nullptr;
/*
Score::~Score()
{
	DeleteComponent("Font");
}
*/
Score* Score::getPtr()
{
	if (score_ptr == nullptr)
	{
		score_ptr = new Score;
		return score_ptr;
	}
	else
		return score_ptr;
}

void Score::DeletePtr()
{
	if (score_ptr != nullptr)
	{
		delete score_ptr;
		score_ptr = nullptr;
	}
}

void Score::SetScore(int v)
{
	point = v;
}

void Score::Update()
{
	f32 width, height;
	AEGfxGetPrintSize(font, std::to_string(point).c_str(), 1.f, &width, &height);
	AEGfxPrint(font, std::to_string(point).c_str(), -width / 2 + pos.x, -height / 2 + pos.y, size, 1, 1, 1, 1);
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

void Score::SaveRankToJson()
{
	std::string dir = GetUserDir();
	CreateDirectory(dir.c_str(), NULL);

	dir = dir + "data.json";

	std::ifstream ijf(dir);

	if (!ijf.is_open())
	{
		std::cout << "FILE NOT FOUND" << std::endl;
		return;
	}
	using json = nlohmann::json;
	json data;
	ijf.seekg(0, std::ios::end);
	if (ijf.tellg() != 0) {
		ijf.seekg(0);
		ijf >> data;
	}
	ijf.close();
	
	SortRank();
	json rank_data;
	for (auto& r : rank)
		rank_data[r.first] = r.second;

	data["RANK"] = rank_data;

	std::ofstream jf(dir);
	jf << data.dump(4);

	jf.close();
}

void Score::LoadRankFromJson()
{
	std::string dir = GetUserDir();
	dir = dir + "data.json";

	if (dir.empty())
	{
		std::cout << "FILE NOT FOUND::DIRECTORY IS EMPTY" << std::endl;
	}

	std::ifstream jf(dir);

	if (!jf.is_open())
	{
		std::cout << "FILE NOT FOUND::FILE CANT OPEN" << std::endl;
	}

	using json = nlohmann::json;
	json data;
	jf.seekg(0, std::ios::end);
	if (jf.tellg() == 0) {
		jf.close();
		return;
	}
	jf.seekg(0);
	jf >> data;

	auto ch = data.find("RANK");
	if (ch != data.end())
	{
		auto rank_data = data.at("RANK");
		for (auto& r : rank_data.items())
			rank.push_back(std::make_pair(r.key(), r.value().get<int>()));
	}
	SortRank();
	jf.close();
}

void Score::PrintRank()
{
	if (rank.empty())
	{
		std::cout << "LIST IS EMPTY" << std::endl;
		return;
	}
	for (auto& a : rank)
		std::cout << a.first << " | " << a.second << std::endl;
}

void Score::SortRank()
{
	rank.sort([](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
			return a.second > b.second;
	});
}

void Score::UpdateRank(std::string userName, int score)
{
	SortRank();
	if (rank.size() >= maxRank)
		rank.pop_back();
	
	if(userName.empty())
		rank.push_back(std::make_pair("UNKNOWN", score));
	else
		rank.push_back(std::make_pair(userName, score));
}

int Score::GetLowerScore()
{
	if (rank.empty())
		return 0;

	int res = 99900;
	for(auto & r : rank)
		res = min(res, r.second);
	
	return res;
}

int Score::GetTopScore()
{
	if (rank.empty())
		return 0;

	return rank.begin()->second;
}

