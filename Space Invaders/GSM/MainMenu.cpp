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


float dt = 0.0f;
float _dt = 0.02f;
float t = 0.0f;

//About Invader
int move_dir = 1;
int InvaderNum = 66;
int AttackNum = 5;
int CurAttackNum = 0;

float UFO_dt = 0.0f;

int score = 0;

void Levels::MainLevel::Init()
{
	counter = 0;
	std::cout << "Main level Init:" << std::endl;
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	//Init Player
	player = new Player;
	player->InitPlayer();
	player->SetPlayer("player", 25.f, 20.f, 0.f, -300.f, 0.f, 255.f, 0.f);

	//Init Invaders
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

	UFO = new Invader;
	UFO->InitInvader();
	UFO->SetInvader("UFO", InvaderType::UFO, 20.f, 20.f, 0.f, (W_HEIGHT / 2) - 150.f, 255.f, 0.f, 0.f);
	UFO->SetRandomSpawn();
	UFO->SetRandomPoints();
	UFO->alive = false;
	UFO->move = false;
	UFO->Visible(false);

	SetInvaderBullet();
	SetAttaker();

	//Init Scene
	wTop = new Wall;
	wTop->InitWall();
	wTop->SetWall("top", W_WIDTH, 100.f, 0.f, (W_HEIGHT / 2) + 48.f, 255.f, 0.f, 0.f);

	//wBot = new Wall;
	//wBot->InitWall();
	//wBot->SetWall("bot", W_WIDTH, 1.f, 0.f, -(W_HEIGHT / 2) + 1.f, 255.f, 0.f, 0.f);

	wLeft = new Wall;
	wLeft->InitWall();
	wLeft->SetWall("left", 1.f, W_HEIGHT, -(W_WIDTH / 2) + 1.f, 0.f, 255.f, 0.f, 0.f);

	wRight = new Wall;
	wRight->InitWall();
	wRight->SetWall("right", 1.f, W_HEIGHT, (W_WIDTH / 2) - 1.f, 0.f, 255.f, 0.f, 0.f);
}

Invader* Levels::MainLevel::GetLeft()
{
	int idx = COL;
	Invader* tmp = nullptr;

	for (int i = 0; i < COL; i++)
	{
		if (Octopus0[i]->alive && i < idx)
		{
			idx = i;
			tmp = Octopus0[i];
		}
		if (Octopus1[i]->alive && i < idx)
		{
			idx = i;
			tmp = Octopus1[i];
		}
		if (Crab0[i]->alive && i < idx)
		{
			idx = i;
			tmp = Crab0[i];
		}
		if (Crab1[i]->alive && i < idx)
		{
			idx = i;
			tmp = Crab1[i];
		}
		if (Squid[i]->alive && i < idx)
		{
			idx = i;
			tmp = Squid[i];
		}
	}

	return tmp;
}

Invader* Levels::MainLevel::GetRight()
{
	int idx = 0;
	Invader* tmp = nullptr;

	for (int i = 0; i < COL; i++)
	{
		if (Octopus0[i]->alive && i > idx)
		{
			idx = i;
			tmp = Octopus0[i];
		}
		if (Octopus1[i]->alive && i > idx)
		{
			idx = i;
			tmp = Octopus1[i];
		}
		if (Crab0[i]->alive && i > idx)
		{
			idx = i;
			tmp = Crab0[i];
		}
		if (Crab1[i]->alive && i > idx)
		{
			idx = i;
			tmp = Crab1[i];
		}
		if (Squid[i]->alive && i > idx)
		{
			idx = i;
			tmp = Squid[i];
		}
	}

	return tmp;
}

void Levels::MainLevel::SetAttaker()
{
	for (int i = 0; i < COL; i++)
	{
		if (Octopus0[i]->attack)
		{
			Octopus0[i]->attack = false;
		}
		if (Octopus1[i]->attack)
		{
			Octopus1[i]->attack = false;
		}
		if (Crab0[i]->attack)
		{
			Crab0[i]->attack = false;
		}
		if (Crab1[i]->attack)
		{
			Crab1[i]->attack = false;
		}
		if (Squid[i]->attack)
		{
			Squid[i]->attack = false;
		}
	}
	CurAttackNum = 0;

	for (int i = 0; i < COL; i++)
	{
		if (CurAttackNum <= AttackNum)
		{
			if (Octopus0[i]->alive)
			{
				Octopus0[i]->SetAttack();
				if (Octopus0[i]->attack)
				{
					CurAttackNum++;
					Octopus0[i]->SetBullet(missile[0]);
					Octopus0[i]->Attack();
				}
			}
			if (Octopus1[i]->alive)
			{
				Octopus1[i]->SetAttack();
				if (Octopus1[i]->attack)
				{
					CurAttackNum++;
					Octopus1[i]->SetBullet(missile[1]);
					Octopus1[i]->Attack();
				}
			}
			if (Crab0[i]->alive)
			{
				Crab0[i]->SetAttack();
				if (Crab0[i]->attack)
				{
					CurAttackNum++;
					Crab0[i]->SetBullet(missile[2]);
					Crab0[i]->Attack();
				}
			}
			if (Crab1[i]->alive)
			{
				Crab1[i]->SetAttack();
				if (Crab1[i]->attack)
				{
					CurAttackNum++;
					Crab1[i]->SetBullet(missile[3]);
					Crab1[i]->Attack();
				}
			}
			if (Squid[i]->alive)
			{
				Squid[i]->SetAttack();
				if (Squid[i]->attack)
				{
					CurAttackNum++;
					Squid[i]->SetBullet(missile[4]);
					Squid[i]->Attack();
				}
			}
		}
		else
			break;
	}
}

void Levels::MainLevel::SetInvaderBullet()
{
	for (int i = 0; i < InvaderNum; i++)
	{
		missile[i] = new Bullet;
		missile[i]->InitBullet();
		missile[i]->SetSize(2.f, 5.f);
		missile[i]->SetMissileRandom();
		missile[i]->Dead();
	}
}

void Levels::MainLevel::Update()
{
	dt = AEFrameRateControllerGetFrameTime();
	UFO_dt += dt;
	
	//Update the player's position
	TransformComponent* pt = (TransformComponent*)player->FindComponent("Transform");
	player->SetPos(pt->GetPos().x, pt->GetPos().y);

	//Get left & right Most Invader for Invader's move
	ColliderComponent* leftMost = (ColliderComponent*)GetLeft()->FindComponent("Collider");
	ColliderComponent* rightMost = (ColliderComponent*)GetRight()->FindComponent("Collider");

	//Wall collider
	ColliderComponent* lc = (ColliderComponent*)wLeft->FindComponent("Collider");
	ColliderComponent* rc = (ColliderComponent*)wRight->FindComponent("Collider");
	ColliderComponent* tc = (ColliderComponent*)wTop->FindComponent("Collider");

	//Check Wall Invaders Collision
	if (leftMost->IsCollision(lc))
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

			move_dir = -1;
		}
	}
	
	if (rightMost->IsCollision(rc))
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

			move_dir = 1;
		}
	}

	//Move invaders
	if (UFO_dt > UFO->GetSpawnTime())
	{
		//std::cout << "!! UFO has spawned !! Spawn Time : " << UFO->GetSpawnTime() << ", POINTS : " << UFO->GetPoints() << std::endl;
		if (move_dir > 0)
			UFO->SetPos(W_WIDTH / 2 - 21.f, (W_HEIGHT / 2) - 150.f);
		else
			UFO->SetPos(-(W_WIDTH / 2) + 21.f, (W_HEIGHT / 2) - 150.f);

		UFO->SetSpeed(20.f * move_dir);
		UFO->alive = true;
		UFO->Visible(true);
		UFO->move = true;

		UFO->SetRandomSpawn();
		UFO->SetRandomPoints();
		UFO_dt = 0.0f;
	}

	ColliderComponent* uc = (ColliderComponent*)UFO->FindComponent("Collider");
	if (uc->IsCollision(lc) || uc->IsCollision(rc))
	{
		//std::cout << "UFO collision" << std::endl;
		UFO->SetPos(0, -W_HEIGHT);
		UFO->Visible(false);
		UFO->move = false;
		UFO->alive = false;
	}
	for (int i = 0; i < COL; i++)
	{
		float v = 1.0f;
		if (InvaderNum < (InvaderNum / 2))
			v = 10.f;

		Octopus0[i]->SetSpeed(20.f * move_dir * v);
		Octopus1[i]->SetSpeed(20.f * move_dir * v);
		Crab0[i]->SetSpeed(20.f * move_dir * v);
		Crab1[i]->SetSpeed(20.f * move_dir * v);
		Squid[i]->SetSpeed(20.f * move_dir * v);
	}
	
	for (int i = 0; i < COL; i++)
	{
		Octopus0[i]->Move(dt);
		Octopus1[i]->Move(dt);
		Crab0[i]->Move(dt);
		Crab1[i]->Move(dt);
		Squid[i]->Move(dt);
		UFO->Move(dt);
	}
	

	//Bullet
	ColliderComponent* bc = (ColliderComponent*)player->GetBullet()->FindComponent("Collider");
	if (player->GetBullet()->alive)
	{
		player->GetBullet()->Fly(dt);
		//Check Bullet Invaders Collision : If Collision is true -> The invader is dead.
		for (int i = 0; i < COL; i++)
		{
			ColliderComponent* oc1 = (ColliderComponent*)Octopus0[i]->FindComponent("Collider");
			ColliderComponent* oc2 = (ColliderComponent*)Octopus1[i]->FindComponent("Collider");
			ColliderComponent* cc1 = (ColliderComponent*)Crab0[i]->FindComponent("Collider");
			ColliderComponent* cc2 = (ColliderComponent*)Crab1[i]->FindComponent("Collider");
			ColliderComponent* sc = (ColliderComponent*)Squid[i]->FindComponent("Collider");

			if (bc->IsCollision(oc1))
			{
				player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
				player->GetBullet()->Dead();

				Octopus0[i]->Dead();
				score += Octopus0[i]->GetPoints();
				InvaderNum--;
			}
			if (bc->IsCollision(oc2))
			{
				player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
				player->GetBullet()->Dead();

				Octopus1[i]->Dead();
				score += Octopus1[i]->GetPoints();
				InvaderNum--;
			}
			if (bc->IsCollision(cc1))
			{
				player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
				player->GetBullet()->Dead();

				Crab0[i]->Dead();
				score += Crab0[i]->GetPoints();
				InvaderNum--;
			}
			if (bc->IsCollision(cc2))
			{
				player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
				player->GetBullet()->Dead();

				Crab1[i]->Dead();
				score += Crab1[i]->GetPoints();
				InvaderNum--;
			}
			if (bc->IsCollision(sc))
			{
				player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
				player->GetBullet()->Dead();

				Squid[i]->Dead();
				score += Squid[i]->GetPoints();
				InvaderNum--;
			}

			if (UFO->alive)
			{
				if (bc->IsCollision(uc))
				{
					player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
					player->GetBullet()->Dead();

					UFO->SetPos(0, -W_HEIGHT);
					UFO->Visible(false);
					UFO->move = false;
					UFO->alive = false;
					score += UFO->GetPoints();
				}
			}
		}
		
		//Check Bullet Wall Collision : If Bullet hits the wall, the bullet is destroyed.
		if (bc->IsCollision(tc))
		{
			player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
			player->GetBullet()->Dead();
		}
	}


	//Set Attacker
	for (int i = 0; i < COL; i++)
	{
		if (Octopus0[i]->attack)
			Octopus0[i]->GetBullet()->FromInvader(dt);
		if (Octopus1[i]->attack)
			Octopus1[i]->GetBullet()->FromInvader(dt);
		if (Crab0[i]->attack)
			Crab0[i]->GetBullet()->FromInvader(dt);
		if (Crab1[i]->attack)
			Crab1[i]->GetBullet()->FromInvader(dt);
		if (Squid[i]->attack)
			Squid[i]->GetBullet()->FromInvader(dt);
	}
	//SetAttaker();

	//std::cout << "Points : " << score << "\n";
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

	for(int i = 0; i < 5; i++)
		delete missile[i];
}
