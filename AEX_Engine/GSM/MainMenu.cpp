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

GameObject* Planet;

void Levels::MainLevel::Init()
{
	counter = 0;
	std::cout << "Main level Init:" << std::endl;

	Planet = new GameObject;
	Planet->SetID("planet");

	Planet->AddComponent(new TransformComponent(Planet));
	TransformComponent* t = (TransformComponent*)Planet->FindComponent("Transform");
	t->SetScale({ 100, 100 });

	Planet->AddComponent(new SpriteComponent(Planet));
	SpriteComponent* s = (SpriteComponent*)Planet->FindComponent("Sprite");
	s->SetTexture("Assets/PlanetTexture.png");


	player = new GameObject;
	player->SetID("player");
	TransformComponent* Transform = new TransformComponent(player);
	SpriteComponent* Sprite = new SpriteComponent(player);
	PlayerComponent* Player = new PlayerComponent(player);
	RigidbodyComponent* Rigid = new RigidbodyComponent(player);

	player->AddComponent(Transform);
	player->AddComponent(Sprite);
	player->AddComponent(Player);
	player->AddComponent(Rigid);

	Sprite->SetTexture("Assets/mg.png");
	Transform->SetPos({ 100, 100 });
	Transform->SetScale({ 200, 200 });
	
	Planet->AddComponent(new AudioComponent(Planet));
	AudioComponent* a = (AudioComponent*)Planet->FindComponent("Audio");
	a->SetAudio("Assets/bouken.mp3");


}

void Levels::MainLevel::Update()
{
	//std::cout << "Main level Update:" << std::endl;

	TransformComponent* trs = (TransformComponent*)Planet->FindComponent("Transform");
	if (trs)
	{
		trs->SetPos({ trs->GetPos().x + 1, trs->GetPos().y });
		if (trs->GetPos().x > 800)
			trs->SetPos({ -800, trs->GetPos().y });
		
		if (counter % 10 == 0)
			trs->SetRot( trs->GetRot() + 0.5f );
		//trs->SetScale({ trs->GetScale().x * 1.01f, trs->GetScale().y * 1.01f });
		//trs->PrintMatrix();
	}

	SpriteComponent* spr = (SpriteComponent*)Planet->FindComponent("Sprite");
	if (spr)
	{
		SpriteComponent::Color& c = spr->GetColor();
	
		if (counter < 255)
		{
			c.r--;
			c.g++;
			c.b++;
		}
		else
		{
			c.r++;
			c.g--;
			c.b--;
		}
	}

	//If goal was reached change level
	counter++;
	if (counter >= 10000)
	{
		//Change to goal
		//GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GoalLevel);
		counter = 0;
	}
}

void Levels::MainLevel::Exit()
{
	std::cout << "Main level Exit:" << std::endl;
	delete player;
	delete Planet;
}
