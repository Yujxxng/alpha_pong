#include "GameOver.h"
#include "MainMenu.h"
#include "GameStateManager.h"
#include "../ComponentManager/GameObject.h"

#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../Resource/TextureResource.h"

#include <iostream>

s8 fontName0;
void Levels::GameOver::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	fontName0 = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();
}

void Levels::GameOver::Update()
{
	f32 width, height;
	AEGfxGetPrintSize(fontName0, "GAME OVER!", 1.f, &width, &height);
	AEGfxPrint(fontName0, "GAME OVER!", -width / 2, -height / 2 + 0.4f, 1.f, 1.f, 1.f, 1.f, 1.f);

	AEGfxGetPrintSize(fontName0, "*Your Score*", 0.8f, &width, &height);
	AEGfxPrint(fontName0, "*Your Score*", -width / 2, -height / 2 + 0.2f, 0.8f, 1.f, 1.f, 1.f, 1.f);

	AEGfxGetPrintSize(fontName0, to_string(TotalScore).c_str(), 1.f, &width, &height);
	AEGfxPrint(fontName0, to_string(TotalScore).c_str(), -width / 2, -height / 2 + 0.05f, 1.f, 0.f, 1.f, 0.f, 1.f);
}

void Levels::GameOver::Exit()
{
	AEGfxDestroyFont(fontName0);
}
