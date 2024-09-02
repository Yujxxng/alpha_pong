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

bool move_dir = true;

float dt = 0.0f;
float _dt = 0.02f;
float t = 0.0f;

int frameCnt = 0;
void Levels::MainLevel::Init()
{
	counter = 0;
	std::cout << "Main level Init:" << std::endl;
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	player = new Player;
	player->InitPlayer();
	player->SetPlayer("player", 25.f, 20.f, 0.f, -300.f, 0.f, 255.f, 0.f);

	for (int i = 0; i < COL; i++)
	{
		std::string ID = "o0" + to_string(i);
		Octopus0[i] = new Invader();
		Octopus0[i]->InitInvader();
		Octopus0[i]->SetInvader(ID, OCTOPUS, 20.f, 20.f, -(320.f / 2) + 10.f + (30.f * i), 0.f, 255.f, 255.f, 255.f);
		Octopus0[i]->printInfo();

		ID = "o1" + to_string(i);
		Octopus1[i] = new Invader();
		Octopus1[i]->InitInvader();
		Octopus1[i]->SetInvader(ID, OCTOPUS, 20.f, 20.f, -(320.f / 2) + 10.f + (30.f * i), 30.f, 255.f, 255.f, 255.f);
		Octopus1[i]->printInfo();

		ID = "c0" + to_string(i);
		Crab0[i] = new Invader();
		Crab0[i]->InitInvader();
		Crab0[i]->SetInvader(ID, CRAB, 20.f, 20.f, -(320.f / 2) + 10.f + (30.f * i), 60.f, 0.f, 255.f, 0.f);
		Crab0[i]->printInfo();

		ID = "c1" + to_string(i);
		Crab1[i] = new Invader();
		Crab1[i]->InitInvader();
		Crab1[i]->SetInvader(ID, CRAB, 20.f, 20.f, -(320.f / 2) + 10.f + (30.f * i), 90.f, 0.f, 255.f, 0.f);
		Crab1[i]->printInfo();

		ID = "s" + to_string(i);
		Squid[i] = new Invader();
		Squid[i]->InitInvader();
		Squid[i]->SetInvader(ID, SQUID, 20.f, 20.f, -(320.f / 2) + 10.f + (30.f * i), 120.f, 0.f, 0.f, 255.f);
		Squid[i]->printInfo();
	}

	wLeft = new Wall;
	wLeft->InitWall();
	wLeft->SetWall("left", 1.f, W_HEIGHT, -(W_WIDTH / 2) + 1.f, 0.f, 255.f, 0.f, 0.f);

	wRight = new Wall;
	wRight->InitWall();
	wRight->SetWall("right", 1.f, W_HEIGHT, (W_WIDTH / 2) - 1.f, 0.f, 255.f, 0.f, 0.f);

}

void Levels::MainLevel::Update()
{
	dt = AEFrameRateControllerGetFrameTime();

	ColliderComponent* o0c = (ColliderComponent*)Octopus0[0]->FindComponent("Collider");
	ColliderComponent* o10c = (ColliderComponent*)Octopus0[10]->FindComponent("Collider");
	ColliderComponent* lc = (ColliderComponent*)wLeft->FindComponent("Collider");
	ColliderComponent* rc = (ColliderComponent*)wRight->FindComponent("Collider");

	if (o0c->IsCollision(lc))
	{
		for (int i = 0; i < COL; i++)
		{
			Octopus0[i]->SetSpeed(0.f);
			Octopus1[i]->SetSpeed(0.f);
			Crab0[i]->SetSpeed(0.f);
			Crab1[i]->SetSpeed(0.f);
			Squid[i]->SetSpeed(0.f);

			Octopus0[i]->SetPos(Octopus0[i]->GetPos().x + 1.f, Octopus0[i]->GetPos().y);
			Octopus1[i]->SetPos(Octopus1[i]->GetPos().x + 1.f, Octopus1[i]->GetPos().y);
			Crab0[i]->SetPos(Crab0[i]->GetPos().x + 1.f, Crab0[i]->GetPos().y);
			Crab1[i]->SetPos(Crab1[i]->GetPos().x + 1.f, Crab1[i]->GetPos().y);
			Squid[i]->SetPos(Squid[i]->GetPos().x + 1.f, Squid[i]->GetPos().y);

			Octopus0[i]->SetPos(Octopus0[i]->GetPos().x, Octopus0[i]->GetPos().y - 20.f);
			Octopus1[i]->SetPos(Octopus1[i]->GetPos().x, Octopus1[i]->GetPos().y - 20.f);
			Crab0[i]->SetPos(Crab0[i]->GetPos().x, Crab0[i]->GetPos().y - 20.f);
			Crab1[i]->SetPos(Crab1[i]->GetPos().x, Crab1[i]->GetPos().y - 20.f);
			Squid[i]->SetPos(Squid[i]->GetPos().x, Squid[i]->GetPos().y - 20.f);

			move_dir = false;
		}
	}
	
	if (o10c->IsCollision(rc))
	{
		for (int i = 0; i < COL; i++)
		{
			Octopus0[i]->SetSpeed(0.f);
			Octopus1[i]->SetSpeed(0.f);
			Crab0[i]->SetSpeed(0.f);
			Crab1[i]->SetSpeed(0.f);
			Squid[i]->SetSpeed(0.f);

			Octopus0[i]->SetPos(Octopus0[i]->GetPos().x - 1.f, Octopus0[i]->GetPos().y);
			Octopus1[i]->SetPos(Octopus1[i]->GetPos().x - 1.f, Octopus1[i]->GetPos().y);
			Crab0[i]->SetPos(Crab0[i]->GetPos().x - 1.f, Crab0[i]->GetPos().y);
			Crab1[i]->SetPos(Crab1[i]->GetPos().x - 1.f, Crab1[i]->GetPos().y);
			Squid[i]->SetPos(Squid[i]->GetPos().x - 1.f, Squid[i]->GetPos().y);

			Octopus0[i]->SetPos(Octopus0[i]->GetPos().x, Octopus0[i]->GetPos().y - 20.f);
			Octopus1[i]->SetPos(Octopus1[i]->GetPos().x, Octopus1[i]->GetPos().y - 20.f);
			Crab0[i]->SetPos(Crab0[i]->GetPos().x, Crab0[i]->GetPos().y - 20.f);
			Crab1[i]->SetPos(Crab1[i]->GetPos().x, Crab1[i]->GetPos().y - 20.f);
			Squid[i]->SetPos(Squid[i]->GetPos().x, Squid[i]->GetPos().y - 20.f);

			move_dir = true;
		}
	}

	for (int i = 0; i < COL; i++)
	{
		Octopus0[i]->SetSpeed(20.f);
		Octopus1[i]->SetSpeed(20.f);
		Crab0[i]->SetSpeed(20.f);
		Crab1[i]->SetSpeed(20.f);
		Squid[i]->SetSpeed(20.f);
	}

	if (move_dir)
	{
		for (int i = 0; i < COL; i++)
		{
			Octopus0[i]->MoveLeft(dt);
			Octopus1[i]->MoveLeft(dt);
			Crab0[i]->MoveLeft(dt);
			Crab1[i]->MoveLeft(dt);
			Squid[i]->MoveLeft(dt);
		}
	}
	else
	{
		for (int i = 0; i < COL; i++)
		{
			Octopus0[i]->MoveRight(dt);
			Octopus1[i]->MoveRight(dt);
			Crab0[i]->MoveRight(dt);
			Crab1[i]->MoveRight(dt);
			Squid[i]->MoveRight(dt);
		}
	}
	/*
	//If goal was reached change level
	counter++;
	if (counter >= 10000)
	{
		//Change to goal
		//GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GoalLevel);
		counter = 0;
	}
	*/
}

void Levels::MainLevel::Exit()
{
	//std::cout << "Main level Exit:" << std::endl;
	delete player;

	for (int i = 0; i < COL; i++)
	{
		delete Octopus0[i];
		delete Octopus1[i];
		delete Crab0[i];
		delete Crab1[i];
		delete Squid[i];
	}
}
