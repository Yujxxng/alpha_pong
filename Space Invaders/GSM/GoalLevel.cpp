#include "GoalLevel.h"
#include "GameStateManager.h"
#include "../ComponentManager/GameObject.h"
#include "../ComponentManager/EventManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"
#include <iostream>

s8 fontName2;
void Levels::GoalLevel::Init()
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	fontName2 = AEGfxCreateFont("Assets/space_invaders.ttf", 30);

}

void Levels::GoalLevel::Update()
{
	//std::cout << "Goal level UPDATE:" << std::endl;
	//std::cout << "YOU WIN!" << std::endl;

	//after something. change level to exit
	//GSM::GameStateManager::GetGSMPtr()->ChangeLevel(nullptr);
	
	f32 width, height;
	AEGfxGetPrintSize(fontName2, "CLEAR!", 1.f, &width, &height);
	AEGfxPrint(fontName2, "CLEAR!", -width / 2, -height / 2, 1.f, 1.f, 1.f, 1.f, 1.f);
	//AEGfxPrint(fontName2, to_string(_result).c_str(), 0.f, 0.2f, 1.f, 1.f, 1.f, 1.f, 1.f);

}

void Levels::GoalLevel::Exit()
{
	AEGfxDestroyFont(fontName2);
}
