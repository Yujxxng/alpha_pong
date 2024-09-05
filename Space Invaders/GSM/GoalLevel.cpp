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

void Levels::GoalLevel::Init()
{
	AEGfxSetBackgroundColor(0.0f, 1.0f, 1.0f);
	//std::cout << "Goal level INIT:" << std::endl;
	//std::cout << "YOU WIN!" << std::endl;
}

void Levels::GoalLevel::Update()
{
	//std::cout << "Goal level UPDATE:" << std::endl;
	//std::cout << "YOU WIN!" << std::endl;

	//after something. change level to exit
	//GSM::GameStateManager::GetGSMPtr()->ChangeLevel(nullptr);
}

void Levels::GoalLevel::Exit()
{
	//std::cout << "Goal level Exit:" << std::endl;
}
