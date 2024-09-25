#include "MainMenu.h"
#include "GoalLevel.h"
#include "GameStateManager.h"
#include "../ComponentManager/GameObject.h"

#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../Resource/TextureResource.h"

#include "../Object/TextInputBox.h"

#include <iostream>

s8 fontName2;
void Levels::GoalLevel::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	fontName2 = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();
}

void Levels::GoalLevel::Update()
{
	f32 width, height;
	AEGfxGetPrintSize(fontName2, "CLEAR!", 1.f, &width, &height);
	AEGfxPrint(fontName2, "CLEAR!", -width / 2, -height / 2 + 0.4f, 1.f, 1.f, 1.f, 1.f, 1.f);
	
	AEGfxGetPrintSize(fontName2, "*Your Score*", 0.8f, &width, &height);
	AEGfxPrint(fontName2, "*Your Score*", -width / 2, -height / 2 + 0.2f, 0.8f, 1.f, 1.f, 1.f, 1.f);

	AEGfxGetPrintSize(fontName2, to_string(TotalScore).c_str(), 1.f, &width, &height);
	AEGfxPrint(fontName2, to_string(TotalScore).c_str(), -width / 2, -height / 2 + 0.05f, 1.f, 0.f, 1.f, 0.f, 1.f);
}

void Levels::GoalLevel::Exit()
{
}
