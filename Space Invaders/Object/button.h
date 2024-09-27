#pragma once
#include "../Utils/myUtils.h"
#include <string>
#include <vector>

class Button
{
	AEGfxVertexList* mesh;
	s8 font;

	AEVec2 pos{0.f, -200.f};
	AEVec2 size;
	Color color{ 255, 255, 255 };

	std::string text{};
	float textSize = 1.f;
	Color textColor{ 255, 255, 255 };

public:
	bool actived = false;

	Button();
	~Button();

	void Update();

	void DrawButton();
	void DrawButtonText();

	void SetPos(float x, float y);
	void SetText(std::string txt);
	void SetTextColor(unsigned char r, unsigned char g, unsigned char b);

	bool isCollision(s32 x, s32 y);
};