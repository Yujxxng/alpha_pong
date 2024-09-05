#include "Title.h"
#include "MainMenu.h"
#include "GameStateManager.h"
#include "../ComponentManager/GameObject.h"
#include "../ComponentManager/EventManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"
#include <iostream>

s8 fontName1;
float titleDt = 0.0f;
float t = 0.0f;
int idx = 0;

static AEGfxTexture* Logo[2];

void Levels::Title::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	fontName1 = AEGfxCreateFont("Assets/space_invaders.ttf", 30);
	Logo[0] = AEGfxTextureLoad("Assets/space_invaders/logo.png");
	Logo[1] = AEGfxTextureLoad("Assets/space_invaders/logo1.png");
}

void Levels::Title::Update()
{
	titleDt += static_cast<float>(AEFrameRateControllerGetFrameTime());
	t += static_cast<float>(AEFrameRateControllerGetFrameTime());

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
	AEGfxSetColorToMultiply(1, 1, 1, 1);
	AEGfxSetColorToAdd(0, 0, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

	if (t > 1.0f)
	{
		idx = (idx + 1) % 2;
		t = 0.0f;
	}
	AEGfxTextureSet(Logo[idx], 0, 0);
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, 258.f, 165.f);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, 0.f, 100.f);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetTransform(transform.m);

	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	AEGfxMeshFree(mesh);

	float a = sinf(PI * titleDt);

	f32 width, height;
	AEGfxGetPrintSize(fontName1, "CLICK TO START", 0.5f, &width, &height);
	AEGfxPrint(fontName1, "CLICK TO START", -width / 2, -height / 2 - 0.3f, 0.5f, 1, 1, 1, fabsf(a));

	AEGfxPrint(fontName1, "¨Ï 2024. Yujung All rights reserved.", -0.44f, - 0.95f, 0.3f, 1, 1, 1, 1);
	
	if(AEInputCheckCurr(AEVK_LBUTTON))
		GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::MainLevel);
}

void Levels::Title::Exit()
{
	AEGfxDestroyFont(fontName1);
	for(int i = 0; i < 2; i++)
		AEGfxTextureUnload(Logo[i]);
}
