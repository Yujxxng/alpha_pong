#include "Intro.h"
#include "Title.h"
#include "MainMenu.h"

#include "GameStateManager.h"

#include "../ComponentManager/GameObject.h"
#include "../Object/TextInputBox.h"

#include <iostream>
#include <string>

s8 IntroFont;

AEGfxTexture* invaders_img[4];
AEGfxTexture* key_img[3];

void Levels::Intro::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	IntroFont = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();
	invaders_img[0] = AEGfxTextureLoad("Assets/space_invaders/ufo_white.png");
	invaders_img[1] = ResourceManager::GetPtr()->Get<TextureResource>("Assets/space_invaders/squid0.png")->GetData();
	invaders_img[2] = ResourceManager::GetPtr()->Get<TextureResource>("Assets/space_invaders/crab1.png")->GetData();
	invaders_img[3] = AEGfxTextureLoad("Assets/space_invaders/octopus_green.png");
	
	key_img[0] = AEGfxTextureLoad("Assets/space_invaders/arrowL.png");
	key_img[1] = AEGfxTextureLoad("Assets/space_invaders/arrowR.png");
	key_img[2] = AEGfxTextureLoad("Assets/space_invaders/space.png");
}

void Levels::Intro::Update()
{
	float a = 1.f;
	float fontSize = 0.7f;

	f32 width, height;
	AEGfxGetPrintSize(IntroFont, "PRESS ANY KEY", 0.5f, &width, &height);
	AEGfxPrint(IntroFont, "PRESS ANY KEY", -width / 2 + 0.73f, -height / 2 + 0.95f, 0.5f, 1, 1, 1, a);

	AEGfxGetPrintSize(IntroFont, "*CONTROLS*", 0.6f, &width, &height);
	AEGfxPrint(IntroFont, "*CONTROLS*", -width / 2, -height / 2 + 0.63f, fontSize, 1, 1, 1, a);
	AEGfxPrint(IntroFont, "  = MOVE", -0.04f, 0.48f, fontSize, 0, 1, 0, a);
	AEGfxPrint(IntroFont, "= ATTACK", 0.0f, 0.38f, fontSize, 0, 1, 0, a);

	Levels::Intro::DrawTexture(key_img[0], -60.f, 150.f, 25.f, 25.f);
	Levels::Intro::DrawTexture(key_img[1], -25.f, 150.f, 25.f, 25.f);
	Levels::Intro::DrawTexture(key_img[2], -42.f, 120.f, 60.f, 25.f);

	AEGfxGetPrintSize(IntroFont, "*SCORE ADVANCE TABLE*", fontSize, &width, &height);
	AEGfxPrint(IntroFont, "*SCORE ADVANCE TABLE*", -width / 2, -height / 2, fontSize, 1, 1, 1, a);


	Levels::Intro::DrawTexture(invaders_img[0], -65.f, -40.f, 30.f, 16.7f);
	AEGfxPrint(IntroFont, "= ?  MYSTERY", -0.17f, -0.15f, fontSize, 1, 1, 1, a);

	Levels::Intro::DrawTexture(invaders_img[1], -63.f, -70.f, 20.f, 20.f);
	AEGfxPrint(IntroFont, "= 30   POINTS", -0.17f, -0.25f, fontSize, 1, 1, 1, a);
	
	Levels::Intro::DrawTexture(invaders_img[2], -63.f, -100.f, 25.f, 25.f);
	AEGfxPrint(IntroFont, "= 20   POINTS", -0.17f, -0.35f, fontSize, 1, 1, 1, a);

	Levels::Intro::DrawTexture(invaders_img[3], -63.f, -130.f, 23.f, 23.f);
	AEGfxPrint(IntroFont, "= 1 0   POINTS", -0.17f, -0.45f, fontSize, 0, 1, 0, a);
	
	for (const auto& key : GSM::GameStateManager::GetGSMPtr()->anyKeys)
	{
		if (AEInputCheckTriggered(key))
		{
			GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::MainLevel);
		}
	}
}

void Levels::Intro::Exit()
{
	AEGfxTextureUnload(invaders_img[0]);
	AEGfxTextureUnload(invaders_img[3]);

	for(int i = 0; i < 3; i++)
		AEGfxTextureUnload(key_img[i]);
}

void Levels::Intro::DrawTexture(AEGfxTexture* tex, float px, float py, float sx, float sy)
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
	AEGfxSetColorToMultiply(1, 1, 1, 1);
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
