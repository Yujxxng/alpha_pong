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
bool save = false;
int activeKey = -1;

void Levels::GameOver::Init()
{
	save = false;
	activeKey = -1;
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	fontName0 = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();

	btn[0].SetPos(0.f, -200.f);
	btn[0].SetText("EXIT");

	btn[1].SetPos(0.f, -150.f);
	btn[1].SetText("RETRY");

	btn[2].SetPos(0.f, -100.f);
	if(RankedIn)
		btn[2].SetText("ADD TO RANK");
	else
		btn[2].SetText("VIEW RANKINGS");
}

void Levels::GameOver::Update()
{
	f32 width, height;
	AEGfxGetPrintSize(fontName0, "GAME OVER!", 0.3f, &width, &height);
	AEGfxPrint(fontName0, "GAME OVER!", -width / 2, -height / 2 + 0.7f, 0.3f, 1.f, 1.f, 1.f, 1.f);
	
	AEGfxGetPrintSize(fontName0, "*YOUR SCORE*", 0.2f, &width, &height);
	AEGfxPrint(fontName0, "*YOUR SCORE*", -width / 2, -height / 2 + 0.5f, 0.2f, 1.f, 1.f, 1.f, 1.f);

	AEGfxGetPrintSize(fontName0, to_string(TotalScore).c_str(), 0.25f, &width, &height);
	AEGfxPrint(fontName0, to_string(TotalScore).c_str(), -width / 2, -height / 2 + 0.35f, 0.25f, 0.f, 1.f, 0.f, 1.f);

	std::string rankStr, hiStr;
	int r = Score::getPtr()->GetRank(TotalScore);

	if (RankedIn)
		rankStr = "RANK-IN : " + std::to_string(r + 1);
	else
		rankStr = "RANK-OUT";

	AEGfxGetPrintSize(fontName0, rankStr.c_str(), 0.1f, &width, &height);
	AEGfxPrint(fontName0, rankStr.c_str(), -width / 2, -height / 2 + 0.22f, 0.1f, 1.f, 1.f, 0.f, 1.f);

	hiStr = "HI-SCORE : " + to_string(HighScore);
	AEGfxGetPrintSize(fontName0, hiStr.c_str(), 0.1f, &width, &height);
	AEGfxPrint(fontName0, hiStr.c_str(), -width / 2, -height / 2 + 0.15f, 0.1f, 1.f, 1.f, 0.f, 1.f);

	//AEGfxGetPrintSize(fontName0, to_string(HighScore).c_str(), 0.1f, &width, &height);
	//AEGfxPrint(fontName0, to_string(HighScore).c_str(), -width / 2 + 0.2f, -height / 2 + 0.15f, 0.1f, 1.f, 1.f, 0.f, 1.f);

	s32 pX, pY;
	AEInputGetCursorPosition(&pX, &pY);
	
	if (btn[2].isCollision(pX - (W_WIDTH / 2), (W_HEIGHT / 2) - pY))
	{
		btn[2].SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			if (RankedIn)
			{
				Score::getPtr()->UpdateRank(textBox.GetText(), TotalScore);
				Score::getPtr()->SaveRankToJson();
				save = true;
				GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Test);
			}
			else
				GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Test);
		}
	}
	else
		btn[2].SetTextColor(255, 255, 255);

	//Mouse
	if (btn[1].isCollision(pX - (W_WIDTH / 2), (W_HEIGHT / 2) - pY))
	{
		if (btn[0].actived)
		{
			btn[0].actived = false;
			btn[2].actived = false;
		}
		
			btn[1].SetTextColor(255, 0, 255);
			if (AEInputCheckTriggered(AEVK_LBUTTON))
				GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Intro);
	}
	else
		btn[1].SetTextColor(255, 255, 255);

	if (btn[0].isCollision(pX - (W_WIDTH / 2), (W_HEIGHT / 2) - pY))
	{
		if (btn[1].actived)
		{
			btn[1].actived = false;
			btn[2].actived = false;
		}

			btn[0].SetTextColor(255, 0, 255);
			if (AEInputCheckTriggered(AEVK_LBUTTON))
				GSM::GameStateManager::GetGSMPtr()->gGameRunning = 0;
	}
	else
		btn[0].SetTextColor(255, 255, 255);

	//Key_Up
	if (AEInputCheckTriggered(AEVK_UP))
	{
		if (activeKey == -1)
			activeKey = 2;
		else
		{
			if (activeKey < 2)
				activeKey++;
		}

		for (int i = 0; i < 3; i++)
		{
			if (i == activeKey)
				btn[i].actived = true;
			else
				btn[i].actived = false;
		}
	}

	//Key_Down
	if (AEInputCheckTriggered(AEVK_DOWN))
	{
		if (activeKey == -1)
			activeKey = 2;
		else
		{
			if (activeKey <= 2 && activeKey > 0)
				activeKey--;
		}

		for (int i = 0; i < 3; i++)
		{
			if (i == activeKey)
				btn[i].actived = true;
			else
				btn[i].actived = false;
		}
	}

	if (btn[1].actived)
	{
		btn[1].SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_RETURN))
			GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Intro);
	}
	if(btn[0].actived)
	{
		btn[0].SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_RETURN))
			GSM::GameStateManager::GetGSMPtr()->gGameRunning = 0;
	}
	if (btn[2].actived)
	{
		btn[2].SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_RETURN))
		{
			if (RankedIn)
			{
				//Score::getPtr()->UpdateRank(textBox.GetText(), TotalScore);
				//Score::getPtr()->SaveRankToJson();
				save = true;
				GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Test);
			}
			else
				GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Test);
		}
	}

	if(RankedIn)
		textBox.Update(static_cast<float>(AEFrameRateControllerGetFrameTime()));
	btn[0].Update();
	btn[1].Update();
	btn[2].Update();
}

void Levels::GameOver::Exit()
{

	if (save == false && RankedIn == true)
	{
		Score::getPtr()->UpdateRank("", TotalScore);
		Score::getPtr()->SaveRankToJson();
	}
}
