#include "GameOver.h"
#include "GameStateManager.h"
#include "../ComponentManager/GameObject.h"
#include "../ComponentManager/EventManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"
#include <iostream>

s8 fontName0;
void Levels::GameOver::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	std::cout << "Game Over INIT:" << std::endl;
	std::cout << "GAMEOVER" << std::endl;

	fontName0 = AEGfxCreateFont("Assets/space_invaders.ttf", 30);
}

void Levels::GameOver::Update()
{
	AEGfxPrint(fontName0, "GAMEOVER", -0.33f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f);
	//std::cout << "Goal level UPDATE:" << std::endl;
	//std::cout << "YOU WIN!" << std::endl;

	//after something. change level to exit
	//GSM::GameStateManager::GetGSMPtr()->ChangeLevel(nullptr);
}

void Levels::GameOver::Exit()
{
	std::cout << "GAMEOVER Exit:" << std::endl;
	AEGfxDestroyFont(fontName0);
}
