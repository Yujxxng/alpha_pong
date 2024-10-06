#include "Test.h"
#include "GameStateManager.h"
#include "Intro.h"
#include "MainMenu.h"

#include "../ComponentManager/GameObject.h"
#include "../Object/TextInputBox.h"

#include <iostream>
#include <string>

s8 Testfont;
void Levels::Test::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	Testfont = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();

	btn0.SetPos(0.f, -150.f);
	btn0.SetText("RETRY");

	btn1.SetPos(0.f, -200.f);
	btn1.SetText("EXIT");

	testScore = Score::getPtr();
	if(Score::getPtr()->getList().empty())
		testScore->LoadRankFromJson();
	testScore->PrintRank();
}

void Levels::Test::Update()
{
	f32 width, height;
	AEGfxGetPrintSize(Testfont, "Ranking", 1.f, &width, &height);
	AEGfxPrint(Testfont, "Ranking", -width / 2, -height / 2 + 0.75f, 1.f, 1.f, 1.f, 1.f, 1.f);

	s32 pX, pY;
	AEInputGetCursorPosition(&pX, &pY);

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
		{
			testScore->SaveRankToJson();
			GSM::GameStateManager::GetGSMPtr()->gGameRunning = 0;
		}
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
	if (btn1.actived)
	{
		btn1.SetTextColor(255, 0, 255);
		if (AEInputCheckTriggered(AEVK_RETURN))
			GSM::GameStateManager::GetGSMPtr()->gGameRunning = 0;
	}

	rankBoard.Update();
	btn0.Update();
	btn1.Update();
}

void Levels::Test::Exit()
{
}
