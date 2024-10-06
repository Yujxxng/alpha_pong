#pragma once

#include "../ComponentManager/GameObject.h"

#include "../Utils/myUtils.h"
#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../ComponentManager/EventManager.h"

#include <list>
#include <string>
class Score : public GameObject
{
	Score() = default;
	~Score() = default;
	Score(const Score&) = delete;
	const Score& operator=(const Score& other) = delete;

	s8 font = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();
	
	float size{ 0.8f };
	AEVec2 pos{ 0.f, 0.83f };
	Color color{ 255, 255, 255 };

	int point = 0;
	
	std::list<pair<std::string, int>> rank;
	int unknownNum = 0;
	int maxRank = 5;

	static Score* score_ptr;
public:
	static Score* getPtr();
	static void DeletePtr();

	void SetScore(int v);
	void SetStr();

	void AddPoint(int v) { point += v; }
	void Update();

	float GetSize() const { return size; }
	AEVec2 GetPos() const { return pos; }
	int getPoint() const { return point; }
	int getRankSize() const { return (int)rank.size(); }
	std::list<pair<std::string, int>> getList() const { return rank; }

	void SaveRankToJson();
	void LoadRankFromJson();

	void PrintRank();
	void SortRank();
	void UpdateRank(std::string userName, int point);

	int GetLowerScore();
	int GetTopScore();
	int GetRank(int userScore);
};