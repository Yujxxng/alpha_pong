#include "MainMenu.h"
#include "GoalLevel.h"
#include "GameStateManager.h"

#include "../GSM/Intro.h"
#include "../GSM/GameOver.h"
#include "../GSM/Test.h"

#include "../ComponentManager/GameObject.h"

#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../Resource/TextureResource.h"

#include "../Object/TextInputBox.h"

#include <iostream>

s8 fontName2;
void Levels::GoalLevel::Init()
{
	activeKey = -1;
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	fontName2 = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();

	goal_btn[0].SetPos(0.f, -200.f);
	goal_btn[0].SetText("EXIT");

	goal_btn[1].SetPos(0.f, -150.f);
	goal_btn[1].SetText("RETRY");

	goal_btn[2].SetPos(0.f, -100.f);
	goal_btn[2].SetText("ADD TO RANK");
}

void Levels::GoalLevel::Update()
{
	f32 width, height;
	AEGfxGetPrintSize(fontName2, "CLEAR!", 0.3f, &width, &height);
	AEGfxPrint(fontName2, "CLEAR!", -width / 2, -height / 2 + 0.55f, 0.3f, 1.f, 1.f, 1.f, 1.f);
	
	AEGfxGetPrintSize(fontName2, "*YOUR SCORE*", 0.2f, &width, &height);
	AEGfxPrint(fontName2, "*YOUR SCORE*", -width / 2, -height / 2 + 0.35f, 0.2f, 1.f, 1.f, 1.f, 1.f);

	AEGfxGetPrintSize(fontName2, to_string(TotalScore).c_str(), 0.25f, &width, &height);
	AEGfxPrint(fontName2, to_string(TotalScore).c_str(), -width / 2, -height / 2 + 0.2f, 0.25f, 0.f, 1.f, 0.f, 1.f);

	std::string hiStr = "HI-SCORE : " + to_string(HighScore);
	AEGfxGetPrintSize(fontName2, hiStr.c_str(), 0.1f, &width, &height);
	AEGfxPrint(fontName2, hiStr.c_str(), -width / 2, -height / 2, 0.1f, 1.f, 1.f, 0.f, 1.f);

	s32 pX, pY;
	AEInputGetCursorPosition(&pX, &pY);

	if (goal_btn[2].isCollision(pX - (W_WIDTH / 2), (W_HEIGHT / 2) - pY))
	{
		goal_btn[2].SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			Score::getPtr()->UpdateRank(goal_textBox.GetText(), TotalScore);
			Score::getPtr()->SaveRankToJson();
			GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Test);
		}
	}
	else
		goal_btn[2].SetTextColor(255, 255, 255);

	//Mouse
	if (goal_btn[1].isCollision(pX - (W_WIDTH / 2), (W_HEIGHT / 2) - pY))
	{
		if (goal_btn[0].actived)
		{
			goal_btn[0].actived = false;
			goal_btn[2].actived = false;
		}

		goal_btn[1].SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_LBUTTON))
			GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Intro);
	}
	else
		goal_btn[1].SetTextColor(255, 255, 255);

	if (goal_btn[0].isCollision(pX - (W_WIDTH / 2), (W_HEIGHT / 2) - pY))
	{
		if (goal_btn[1].actived)
		{
			goal_btn[1].actived = false;
			goal_btn[2].actived = false;
		}

		goal_btn[0].SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_LBUTTON))
			GSM::GameStateManager::GetGSMPtr()->gGameRunning = 0;
	}
	else
		goal_btn[0].SetTextColor(255, 255, 255);

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
				goal_btn[i].actived = true;
			else
				goal_btn[i].actived = false;
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
				goal_btn[i].actived = true;
			else
				goal_btn[i].actived = false;
		}
	}

	if (goal_btn[1].actived)
	{
		goal_btn[1].SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_RETURN))
			GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Intro);
	}
	if (goal_btn[0].actived)
	{
		goal_btn[0].SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_RETURN))
			GSM::GameStateManager::GetGSMPtr()->gGameRunning = 0;
	}
	if (goal_btn[2].actived)
	{
		goal_btn[2].SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_RETURN))
		{
			save = true;
			GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new Levels::Test);
		}
	}

	
	goal_textBox.Update(static_cast<float>(AEFrameRateControllerGetFrameTime()));
	goal_btn[0].Update();
	goal_btn[1].Update();
	goal_btn[2].Update();
}

void Levels::GoalLevel::Exit()
{
}
