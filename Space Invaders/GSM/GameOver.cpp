#include "GameOver.h"
#include "MainMenu.h"
#include "GameStateManager.h"

#include "../GSM/Intro.h"
#include "../GSM/Test.h"

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

	btn0.SetPos(0.f, -150.f);
	btn0.SetText("RETRY");

	btn1.SetPos(0.f, -200.f);
	btn1.SetText("EXIT");

	btn2.SetPos(0.f, -100.f);
	btn2.SetText("ADD TO RANK");
}

void Levels::GameOver::Update()
{
	f32 width, height;
	AEGfxGetPrintSize(fontName0, "GAME OVER!", 1.f, &width, &height);
	AEGfxPrint(fontName0, "GAME OVER!", -width / 2, -height / 2 + 0.7f, 1.f, 1.f, 1.f, 1.f, 1.f);

	AEGfxGetPrintSize(fontName0, "*YOUR SCORE*", 0.8f, &width, &height);
	AEGfxPrint(fontName0, "*YOUR SCORE*", -width / 2, -height / 2 + 0.5f, 0.8f, 1.f, 1.f, 1.f, 1.f);

	AEGfxGetPrintSize(fontName0, to_string(TotalScore).c_str(), 1.f, &width, &height);
	AEGfxPrint(fontName0, to_string(TotalScore).c_str(), -width / 2, -height / 2 + 0.35f, 1.f, 0.f, 1.f, 0.f, 1.f);

	std::string tmp = "HI-SCORE : " + to_string(HighScore);
	AEGfxGetPrintSize(fontName0, tmp.c_str(), 0.5f, &width, &height);
	AEGfxPrint(fontName0, "HI-SCORE : ", -width / 2 - 0.05f, -height / 2 + 0.15f, 0.6f, 1.f, 1.f, 0.f, 1.f);

	AEGfxGetPrintSize(fontName0, to_string(HighScore).c_str(), 0.6f, &width, &height);
	AEGfxPrint(fontName0, to_string(HighScore).c_str(), -width / 2 + 0.2f, -height / 2 + 0.15f, 0.6f, 1.f, 1.f, 0.f, 1.f);

	s32 pX, pY;
	AEInputGetCursorPosition(&pX, &pY);

	if (RankedIn)
	{
		textBox.Update(static_cast<float>(AEFrameRateControllerGetFrameTime()));
		btn2.Update();

		if (btn2.isCollision(pX - (W_WIDTH / 2), (W_HEIGHT / 2) - pY))
		{
			btn2.SetTextColor(255, 0, 255);
			if (AEInputCheckTriggered(AEVK_LBUTTON))
			{
				Score::getPtr()->UpdateRank(textBox.GetText(), TotalScore);
				Score::getPtr()->SaveRankToJson();
				GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Test);

			}
		}
		else
			btn2.SetTextColor(255, 255, 255);
	}

	//Mouse
	if (btn0.isCollision(pX - (W_WIDTH / 2), (W_HEIGHT / 2) - pY))
	{
		if (btn1.actived)
			btn1.actived = false;
		
			btn0.SetTextColor(255, 0, 255);
			if (AEInputCheckTriggered(AEVK_LBUTTON))
				GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Intro);
	}
	else
		btn0.SetTextColor(255, 255, 255);

	if (btn1.isCollision(pX - (W_WIDTH / 2), (W_HEIGHT / 2) - pY))
	{
		if (btn0.actived)
			btn0.actived = false;

			btn1.SetTextColor(255, 0, 255);
			if (AEInputCheckTriggered(AEVK_LBUTTON))
				GSM::GameStateManager::GetGSMPtr()->gGameRunning = 0;
	}
	else
		btn1.SetTextColor(255, 255, 255);


	//Key_Up
	if (AEInputCheckTriggered(AEVK_UP))
	{
		btn0.actived = true;
		btn1.actived = false;
	}
	if (btn0.actived)
	{
		btn0.SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_RETURN))
			GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Intro);
	}

	//Key_Down
	if (AEInputCheckTriggered(AEVK_DOWN))
	{
		btn0.actived = false;
		btn1.actived = true;
	}
	if(btn1.actived)
	{
		btn1.SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_RETURN))
			GSM::GameStateManager::GetGSMPtr()->gGameRunning = 0;
	}

	btn0.Update();
	btn1.Update();
}

void Levels::GameOver::Exit()
{

}
