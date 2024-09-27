#include "Test.h"
#include "GameStateManager.h"

#include "../ComponentManager/GameObject.h"
#include "../Object/TextInputBox.h"

#include <iostream>
#include <string>

void Levels::Test::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

void Levels::Test::Update()
{
	rankBoard.Update();
}

void Levels::Test::Exit()
{
}
