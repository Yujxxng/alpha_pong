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
void Levels::Title::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	std::cout << "TITLE INIT:" << std::endl;
	std::cout << "GAMEOVER" << std::endl;

	fontName1 = AEGfxCreateFont("Assets/space_invaders.ttf", 30);
}

void Levels::Title::Update()
{
	AEGfxPrint(fontName1, "PRESS TO START", -0.33f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f);
	//std::cout << "Goal level UPDATE:" << std::endl;
	//std::cout << "YOU WIN!" << std::endl;

	//after something. change level to exit
	//GSM::GameStateManager::GetGSMPtr()->ChangeLevel(nullptr);
}

void Levels::Title::Exit()
{
	std::cout << "Title Exit:" << std::endl;
	AEGfxDestroyFont(fontName1);
}
