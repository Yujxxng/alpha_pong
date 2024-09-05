#pragma once

#include "../ComponentManager/GameObject.h"

#include "../Components/Font.h"
#include "../ComponentManager/EventManager.h"

class Score : public GameObject
{
	float size{};
	AEVec2 pos{};
	Color color{};

	int point = 0;

public:
	~Score();

	void InitScore();
	void SetScore(std::string id, float size, float posX, float posY, float r, float g, float b);
	void SetSize(float s);
	void SetPos(float x, float y);
	void SetColor(float r, float g, float b);
	void SetStr();

	float GetSize() const { return size; }
	AEVec2 GetPos() const { return pos; }
	int getPoint() const { return point; }

	void AddPoint(int v) { point += v; }
	void Reset() { point = 0;}
};