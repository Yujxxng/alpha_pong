#include "RankBoard.h"

#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../Resource/TextureResource.h"
#include "../Object/Score.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>

RankBoard::RankBoard()
{
	font = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();

	f32 width = 0, height = 0;
	AEGfxGetPrintSize(font, "RANK", textSize0, &width, &height);
	col_lines[0] = (AEGfxGetWindowWidth() * width / 2.f) + margin.x;
	boardSize.x += col_lines[0];
	boardSize.y = max(boardSize.y, (AEGfxGetWindowHeight() * height / 2.f) + margin.y);

	AEGfxGetPrintSize(font, "ABCDEFGHIJKLMN", textSize0, &width, &height); // -> name
	col_lines[1] = (AEGfxGetWindowWidth() * width / 2.f) + margin.x;
	boardSize.x += col_lines[1];
	boardSize.y = max(boardSize.y, (AEGfxGetWindowHeight() * height / 2.f) + margin.y);

	AEGfxGetPrintSize(font, "SCORE", textSize0, &width, &height);
	boardSize.x += (AEGfxGetWindowWidth() * width / 2.f) + margin.x;
	boardSize.y = max(boardSize.y, (AEGfxGetWindowHeight() * height / 2.f) + margin.y);

	categoryH = boardSize.y;
	boardSize.y = boardSize.y + (rankAreaH * (RANK_ROW - 1));
	
	col_lines[0] = boardPos.x - (boardSize.x / 2.f) + col_lines[0];
	col_lines[1] = col_lines[0] + col_lines[1];

	row_lines[0] = boardPos.y + (boardSize.y / 2.f) - categoryH;
	for (int i = 1; i < 5; i++)
		row_lines[i] = row_lines[i - 1] - rankAreaH;

	AEGfxMeshStart();

	AEGfxVertexAdd(-0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(-0.5f, -0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(0.5f, -0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(-0.5f, -0.5f, 0xFFFFFFFF, 0.f, 0.f);

	AEGfxVertexAdd(-0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(0.5f, -0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.f);

	float p;
	for (int i = 0; i < 2; i++)
	{
		p = col_lines[i] / boardSize.x;
		AEGfxVertexAdd(p, 0.5f, 0xFFFFFFFF, 0.f, 0.f);
		AEGfxVertexAdd(p, -0.5f, 0xFFFFFFFF, 0.f, 0.f);
	}

	for (int i = 0; i < 5; i++)
	{
		p = row_lines[i] / boardSize.y ;
		AEGfxVertexAdd(-0.5f, p - 0.22f, 0xFFFFFFFF, 0.f, 0.f);
		AEGfxVertexAdd(0.5f, p - 0.22f, 0xFFFFFFFF, 0.f, 0.f);
	}

	mesh = AEGfxMeshEnd();
}

RankBoard::~RankBoard()
{
	AEGfxMeshFree(mesh);
}

void RankBoard::Update()
{
	DrawRankBoard();
	DrawCategories();
	DrawRankers();
}

void RankBoard::DrawRankBoard()
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetColorToMultiply(1, 1, 1, 1);
	AEGfxSetColorToAdd(0, 0, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, boardSize.x + margin.x, boardSize.y + margin.y);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, boardPos.x, boardPos.y);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetTransform(transform.m);

	AEGfxMeshDraw(mesh, AE_GFX_MDM_LINES);
}

void RankBoard::DrawCategories()
{
	float startX = boardPos.x - (boardSize.x / 2.f);
	float startY = boardPos.y + (boardSize.y / 2.f);

	f32 width, height;
	AEGfxGetPrintSize(font, "RANK", textSize0, &width, &height);
	float x = startX * 2.f / AEGfxGetWindowWidth();
	float y = startY * 2.f / AEGfxGetWindowHeight();
	AEGfxPrint(font, "RANK", x + 0.01f, y - (height / 2) - 0.025f, textSize0, 0, 1, 0, 1);

	float ry = (startY - categoryH) * 2.f / AEGfxGetWindowHeight();
	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
			AEGfxPrint(font, std::to_string(i + 1).c_str(), x + 0.095f, ry - (height / 2) - 0.05f - (0.14f * i), textSize0, 1, 0, 1, 1);
		else
			AEGfxPrint(font, std::to_string(i+1).c_str(), x + 0.085f, ry - (height / 2) - 0.05f - (0.14f * i), textSize0, 1, 1, 1, 1);
	}
	AEGfxGetPrintSize(font, "ABCDEFGHIJKLMN", textSize0, &width, &height);
	x = col_lines[0] * 2.f / AEGfxGetWindowWidth();
	AEGfxPrint(font, "NAME", x + (width / 2) - 0.06f, y - (height / 2) - 0.025f, textSize0, 0, 1, 0, 1);


	AEGfxGetPrintSize(font, "SCORE", textSize0, &width, &height);
	x = col_lines[1] * 2.f / AEGfxGetWindowWidth();
	AEGfxPrint(font, "SCORE", x + 0.04f, y - (height / 2) - 0.025f, textSize0, 0, 1, 0, 1);
}

void RankBoard::DrawRankers()
{
	Score::getPtr()->SortRank();
	std::list<pair<std::string, int>> tmp = Score::getPtr()->getList();
	float startY = boardPos.y + (boardSize.y / 2.f);
	float y = (startY - categoryH) * 2.f / AEGfxGetWindowHeight();

	Color textColor = { 1, 0, 1 };
	int cnt = 0;
	for(auto& i : tmp)
	{
		if (cnt >= 5) break;
		std::string name = i.first;
		std::string score = std::to_string(i.second);
		
		if (cnt > 0)
			textColor = { 1, 1, 1 };
		f32 width, height;
		AEGfxGetPrintSize(font, "RANK", textSize0, &width, &height);

		float nameX = 2.f * col_lines[0] / AEGfxGetWindowWidth();
		float scoreX = 2.f * col_lines[1] / AEGfxGetWindowWidth();
		AEGfxPrint(font, name.c_str(), nameX + 0.01f, y - (height / 2) - 0.05f - (0.14f * cnt), textSize0, textColor.r, textColor.g, textColor.b, 1);
		AEGfxPrint(font, score.c_str(), scoreX + 0.025f, y - (height / 2) - 0.05f - (0.14f * cnt), textSize0, textColor.r, textColor.g, textColor.b, 1);
		
		cnt++;
	}

}
