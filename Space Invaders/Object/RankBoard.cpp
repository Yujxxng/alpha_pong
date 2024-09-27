#include "RankBoard.h"

#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../Resource/TextureResource.h"

#include <iostream>
#include <fstream>

RankBoard::RankBoard()
{
	font = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();

	f32 width = 0, height = 0;
	AEGfxGetPrintSize(font, "RANK", textSize0, &width, &height);
	boardSize.x += AEGfxGetWindowWidth() * width / 2.f + margin.x;
	boardSize.y = max(boardSize.y, AEGfxGetWindowHeight() * height / 2.f + margin.y);
	col_lines[0] = boardSize.x;

	AEGfxGetPrintSize(font, "ABCDEFGHIJKLMN", textSize0, &width, &height); // -> name
	boardSize.x += AEGfxGetWindowWidth() * width / 2.f + margin.x;
	boardSize.y = max(boardSize.y, AEGfxGetWindowHeight() * height / 2.f + margin.y);
	col_lines[1] = boardSize.x;

	AEGfxGetPrintSize(font, "SCORE", textSize0, &width, &height);
	boardSize.x += AEGfxGetWindowWidth() * width / 2.f + margin.x;
	boardSize.y = max(boardSize.y, AEGfxGetWindowHeight() * height / 2.f + margin.y);

	AEGfxMeshStart();

	AEGfxVertexAdd(-0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(-0.5f, -0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(0.5f, -0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(-0.5f, -0.5f, 0xFFFFFFFF, 0.f, 0.f);

	AEGfxVertexAdd(-0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(0.5f, -0.5f, 0xFFFFFFFF, 0.f, 0.f);
	AEGfxVertexAdd(0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.f);

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
	float left = boardPos.x - (boardSize.x / 2.f);

	f32 width, height;
	AEGfxGetPrintSize(font, "RANK", textSize0, &width, &height);
	float x = left * 2.f / AEGfxGetWindowWidth();
	float y = boardPos.y * 2.f / AEGfxGetWindowHeight();
	AEGfxPrint(font, "RANK", x + 0.02f, y - (height / 2), textSize0, 0, 0, 1, 1);

	AEGfxGetPrintSize(font, "ABCDEFGHIJKLMN", textSize0, &width, &height);
	left = col_lines[0] - (boardSize.x / 2.f);
	x = left * 2.f / AEGfxGetWindowWidth();
	AEGfxPrint(font, "NAME", x + (width / 2) - 0.04f, y - (height / 2), textSize0, 0, 0, 1, 1);
	//std::cout << x;

	AEGfxGetPrintSize(font, "SCORE", textSize0, &width, &height);
	left = col_lines[1] - (boardSize.x / 2.f);
	x = left * 2.f / AEGfxGetWindowWidth();
	AEGfxPrint(font, "SCORE", x + 0.02f, y - (height / 2), textSize0, 0, 0, 1, 1);
}
