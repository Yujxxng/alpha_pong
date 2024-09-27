#pragma once
#include "../Utils/myUtils.h"
#include <string>
#include <vector>

class RankBoard
{
	const int RANK_COL = 3;
	const int RANK_ROW = 6;

	AEGfxVertexList* mesh;
	s8 font;

	AEVec2 boardPos{ 0.f, 0.f };
	AEVec2 boardSize{ 0.f, 0.f };

	AEVec2 margin{ 10.f, 5.f };

	float col_lines[2];
	float row_lines[5];

	float textSize0 = 0.8f;
	float textSize1 = 0.5f;
public:

	RankBoard();
	~RankBoard();

	void Update();

	void DrawRankBoard();
	void DrawCategories();
};