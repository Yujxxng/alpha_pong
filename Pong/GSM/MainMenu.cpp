#include "MainMenu.h"
#include "GameStateManager.h"
#include "GoalLevel.h"

#include <iostream>

#include "../ComponentManager/GameObject.h"
#include "../ComponentManager/EventManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"
#include "../ComponentManager/ResourceManager.h"

#include "../Object/Racket.h"

Racket* racket;

void Levels::MainLevel::Init()
{
	AEGfxSetBackgroundColor(0.f, 0.f, 0.f);
	
	//racket = new Racket;
	//racket->SetRacketID("test");
	//
	//racket->SetSize(100.f, 100.f);
	//racket->SetPos(100.f, 100.f);
	//racket->SetColor(255.f, 255.f, 255.f);
}

void Levels::MainLevel::Update()
{

#if 0
	counter++;
	if (counter >= 10000)
	{
		//Change to goal
		//GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GoalLevel);
		counter = 0;
	}
#endif
}

void Levels::MainLevel::Exit()
{
	delete racket;
}
