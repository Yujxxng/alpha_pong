#include "Title.h"
#include "Intro.h"
#include "MainMenu.h"
#include "GameStateManager.h"
#include "../ComponentManager/GameObject.h"

#include <iostream>

s8 fontName1;
float titleDt = 0.0f;
float dgDt = 0.0f;
float stop = 0.0f;
float t = 0.0f;
int idx = 0;

bool draw = false;
bool clickable = false;
static AEGfxTexture* Logo[2];
AEGfxTexture* dg;

AEAudio titleBgm;
AEAudioGroup titleGroup;

void Levels::Title::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	fontName1 = AEGfxCreateFont("Assets/space_invaders.ttf", 30);
	Logo[0] = AEGfxTextureLoad("Assets/space_invaders/logo.png");
	Logo[1] = AEGfxTextureLoad("Assets/space_invaders/logo1.png");
	dg = AEGfxTextureLoad("Assets/DigiPen.png");
	dgDt = 0.0f;

	titleGroup = AEAudioCreateGroup();
	titleBgm = *(ResourceManager::GetPtr()->Get<AudioResource>("Assets/space_invaders/Invader Homeworld.mp3")->GetData());
}

void Levels::Title::Update()
{
	titleDt += static_cast<float>(AEFrameRateControllerGetFrameTime());
	t += static_cast<float>(AEFrameRateControllerGetFrameTime());

	float la = 0.f;
	if (!draw)
	{
		if (dgDt < 2.f)
		{
			la = dgDt / 2.f;
			dgDt += static_cast<float>(AEFrameRateControllerGetFrameTime());
			if (dgDt >= 2.f)
			{
				stop += static_cast<float>(AEFrameRateControllerGetFrameTime());
				if (stop >= 2.f)
					dgDt = 2.f;
			}
		}
		else
		{
			la = 2.f - (dgDt - 2.f) / 2.f;
			dgDt += static_cast<float>(AEFrameRateControllerGetFrameTime());
			if (dgDt >= 7.3f)
			{
				draw = true;
				clickable = true;
				AEAudioPlay(titleBgm, titleGroup, 0.5f, 1.f, -1);
			}
		}
	}

	Levels::Title::DrawTexture(dg, 0.f, 29.f, 200.f, 48.f, la);
	if (t > 1.0f)
	{
		idx = (idx + 1) % 2;
		t = 0.0f;
	}

	Levels::Title::DrawTexture(Logo[idx], 0.f, 100.f, 258.f, 165.f, 1.f * draw);

	float a = sinf(PI * titleDt) * draw;

	f32 width, height;
	AEGfxGetPrintSize(fontName1, "PRESS ANY KEY. . .", 0.5f, &width, &height);
	AEGfxPrint(fontName1, "PRESS ANY KEY. . .", -width / 2, -height / 2 - 0.2f, 0.5f, 1, 1, 1, fabsf(a));

	AEGfxPrint(fontName1, "¨Ï 2024. Yujung All rights reserved.", -0.44f, - 0.95f, 0.3f, 1, 1, 1, 1.f * draw);
	
	if (clickable)
	{
		for (const auto& key : GSM::GameStateManager::GetGSMPtr()->anyKeys)
		{
			if (AEInputCheckTriggered(key))
			{
				AEAudioStopGroup(titleGroup);
				GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Intro);
			}
		}
	}
}

void Levels::Title::Exit()
{
	AEGfxDestroyFont(fontName1);
	for(int i = 0; i < 2; i++)
		AEGfxTextureUnload(Logo[i]);
	AEGfxTextureUnload(dg);
	AEAudioUnloadAudioGroup(titleGroup);
}

void Levels::Title::DrawTexture(AEGfxTexture* tex, float px, float py, float sx, float sy, float a)
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxVertexList* mesh = AEGfxMeshEnd();

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetColorToMultiply(1, 1, 1, a);
	AEGfxSetColorToAdd(0, 0, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

	AEGfxTextureSet(tex, 0, 0);
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, sx, sy);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, px, py);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetTransform(transform.m);

	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	AEGfxMeshFree(mesh);
}