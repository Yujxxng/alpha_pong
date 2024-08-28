#include "GoalLevel.h"
#include "GameStateManager.h"

#include <iostream>

void Levels::GoalLevel::Init()
{
	std::cout << "Goal level INIT:" << std::endl;
}

void Levels::GoalLevel::Update()
{
	std::cout << "Goal level UPDATE:" << std::endl;
	std::cout << "YOU WIN!" << std::endl;

	//after something. change level to exit
	GSM::GameStateManager::GetGSMPtr()->ChangeLevel(nullptr);
}

void Levels::GoalLevel::Exit()
{
	std::cout << "Goal level Exit:" << std::endl;
}
