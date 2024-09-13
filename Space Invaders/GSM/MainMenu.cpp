#include "MainMenu.h"
#include "GameStateManager.h"
#include "GoalLevel.h"
#include "GameOver.h"

#include <iostream>

#include "../ComponentManager/GameObject.h"
#include "../ComponentManager/EventManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"

bool stopMain = false;

float dt = 0.0f;
float stopDt = 0.0f;
float _moveDt = 1.f;

//About Invader
int move_dir = 1;
int InvaderNum = 66;
int CurAttackNum = 0;

float UFO_dt = 0.0f;
float idx_dt = 0.0f;

s8 fontName;
AEAudio bgm;
AEAudioGroup bgm_group;
void Levels::MainLevel::Init()
{
	//std::cout << "Main level Init:" << std::endl;
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	fontName = AEGfxCreateFont("Assets/space_invaders.ttf", 30);
	bgm_group = AEAudioCreateGroup();
	bgm = AEAudioLoadMusic("Assets/space_invaders/Invader Homeworld.mp3");
	
	AEAudioPlay(bgm, bgm_group, 0.5f, 1.f, -1);

	//Init Score
	score = new Score;
	score->InitScore();
	score->SetScore("score", 0.8f, 0.f, 0.80f, 255.f, 255.f, 255.f);

	//Init Player
	player = new Player;
	player->InitPlayer();
	player->SetPlayer("player", 25.f, 20.f, 0.f, -200.f, 0.f, 255.f, 0.f);

	//Init Invaders
	for (int i = 0; i < COL; i++)
	{
		std::string ID = "o0" + to_string(i);
		Octopus0[i] = new Invader();
		Octopus0[i]->InitInvader();
		Octopus0[i]->SetInvader(ID, OCTOPUS, 22.f, 22.f, -(320.f / 2) + 10.f + (30.f * i), 0.f, 255.f, 255.f, 255.f);
		//Octopus0[i]->printInfo();

		ID = "o1" + to_string(i);
		Octopus1[i] = new Invader();
		Octopus1[i]->InitInvader();
		Octopus1[i]->SetInvader(ID, OCTOPUS, 22.f, 22.f, -(320.f / 2) + 10.f + (30.f * i), 35.f, 255.f, 255.f, 255.f);
		//Octopus1[i]->printInfo();

		ID = "c0" + to_string(i);
		Crab0[i] = new Invader();
		Crab0[i]->InitInvader();
		Crab0[i]->SetInvader(ID, CRAB, 22.f, 22.f, -(320.f / 2) + 10.f + (30.f * i), 70.f, 0.f, 255.f, 0.f);
		//Crab0[i]->printInfo();

		ID = "c1" + to_string(i);
		Crab1[i] = new Invader();
		Crab1[i]->InitInvader();
		Crab1[i]->SetInvader(ID, CRAB, 22.f, 22.f, -(320.f / 2) + 10.f + (30.f * i), 105.f, 0.f, 255.f, 0.f);
		//Crab1[i]->printInfo();

		ID = "s" + to_string(i);
		Squid[i] = new Invader();
		Squid[i]->InitInvader();
		Squid[i]->SetInvader(ID, SQUID, 20.f, 20.f, -(320.f / 2) + 10.f + (30.f * i), 140.f, 0.f, 0.f, 255.f);
		//Squid[i]->printInfo();
	}

	UFO = new Invader;
	UFO->InitInvader();
	UFO->SetInvader("UFO", InvaderType::UFO, 30.f, 20.f, 0.f, (W_HEIGHT / 2) - 50.f, 255.f, 0.f, 0.f);
	UFO->SetRandomSpawn();
	UFO->SetRandomPoints();
	UFO->alive = false;
	UFO->move = false;
	UFO->Visible(false);

	InitAttacker();
	SetAttacker(2);

	//Init Scene
	wTop = new Wall;
	wTop->InitWall();
	wTop->SetWall("top", W_WIDTH, 100.f, 0.f, (W_HEIGHT / 2) + 48.f, 255.f, 0.f, 0.f);

	wBot = new Wall;
	wBot->InitWall();
	wBot->SetWall("bot", W_WIDTH, 100.f, 0.f, -(W_HEIGHT / 2) - 48.f, 255.f, 0.f, 0.f);

	wLeft = new Wall;
	wLeft->InitWall();
	wLeft->SetWall("left", 100.f, W_HEIGHT, -(W_WIDTH / 2) - 50.f, 0.f, 255.f, 0.f, 0.f);

	wRight = new Wall;
	wRight->InitWall();
	wRight->SetWall("right", 100.f, W_HEIGHT, (W_WIDTH / 2) + 50.f, 0.f, 255.f, 0.f, 0.f);
}

void Levels::MainLevel::Stop()
{
	stopMain = true;
	player->stop = true;
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
	int idx = -1;
	Invader* tmp = nullptr;

	for (int i = COL - 1; i >= 0; i--)
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

Invader* Levels::MainLevel::GetBottom()
{
	float min = 800.f;
	Invader* p = nullptr;
	for (int i = 0; i < COL; i++)
	{
		if (Attacker[i].first)
		{
			if (min > Attacker[i].first->GetPos().y)
			{
				min = Attacker[i].first->GetPos().y;
				p = Attacker[i].first;
			}
		}
	}
	return p;
}

void Levels::MainLevel::UpdateBottom()
{
	for (int i = 0; i < COL; i++)
	{
		if (Squid[i]->alive)
			Attacker[i].first = Squid[i];
		else
			Attacker[i].first = nullptr;

		if (Crab1[i]->alive)
			Attacker[i].first = Crab1[i];

		if (Crab0[i]->alive)
			Attacker[i].first = Crab0[i];

		if (Octopus1[i]->alive)
			Attacker[i].first = Octopus1[i];

		if (Octopus0[i]->alive)
			Attacker[i].first = Octopus0[i];
	}
}

void Levels::MainLevel::UpdateDead()
{
	for (int i = 0; i < COL; i++)
	{
		if (!Squid[i]->alive)
		{
			Squid[i]->Dead();
			Squid[i]->GetBullet()->Dead();
		}

		if (!Crab1[i]->alive)
		{
			Crab1[i]->Dead();
			Crab1[i]->GetBullet()->Dead();
		}
		if (!Crab0[i]->alive)
		{
			Crab0[i]->Dead();
			Crab0[i]->GetBullet()->Dead();
		}
		if (!Octopus1[i]->alive)
		{
			Octopus1[i]->Dead();
			Octopus1[i]->GetBullet()->Dead();
		}
		if (!Octopus0[i]->alive)
		{
			Octopus0[i]->Dead();
			Octopus0[i]->GetBullet()->Dead();
		}
	}
}

void Levels::MainLevel::InitAttacker()
{
	for (int i = 0; i < COL; i++)
	{
		Attacker[i].first = Octopus0[i];
		Attacker[i].second = false;
	}
}

void Levels::MainLevel::SetAttacker(int n)
{
	if (n < 1) return;

	for (int i = 0; i < COL; i++)
	{
		if (CurAttackNum < n)
		{
			if (Attacker[i].first)
			{
				Attacker[i].second = Attacker[i].first->SetAttack();
				if (Attacker[i].second)
				{
					if(InvaderNum < 3)
						Attacker[i].first->SetAttackTime(1.5);
					else
						Attacker[i].first->SetAttackTime(10);

					Attacker[i].first->GetBullet()->SetMissileRandom();
					CurAttackNum++;
				}
			}
		}
		else break;
	}
}

bool Levels::MainLevel::IsAttacker(Invader* invader)
{
	for (int i = 0; i < COL; i++)
	{
		if (invader == Attacker[i].first)
		{
			if (Attacker[i].second)
				return true;
		}
	}
	return false;
}

int Levels::MainLevel::GetLiveAttacker()
{
	int cnt = 0;
	for (int i = 0; i < COL; i++)
	{
		if (Attacker[i].first)
			cnt++;
	}
	return cnt;
}

int Levels::MainLevel::GetLiveInvaders()
{
	int cnt = 0;
	for (int i = 0; i < COL; i++)
	{
		if (Squid[i]->alive)
			cnt++;
		if (Crab1[i]->alive)
			cnt++;
		if (Crab0[i]->alive)
			cnt++;
		if (Octopus1[i]->alive)
			cnt++;
		if (Octopus0[i]->alive)
			cnt++;
	}
	return cnt;
}

void Levels::MainLevel::PrintAttacker()
{
	for (int i = 0; i < COL; i++)
		std::cout << Attacker[i].first->GetID() << " | ";
	std::cout << "\n";
}

void Levels::MainLevel::Update()
{
	AEGfxPrint(fontName, "<SCORE>", -0.26f, 0.87f, 0.7f, 1.f, 1.f, 1.f, 1.f);
	
	AEGfxPrint(fontName, "LIFE : ", 0.5f, 0.915f, 0.5f, 1.f, 1.f, 1.f, 1.f);
	if (GetLiveInvaders() > 0)
	{
		if(!stopMain)
			dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
		else
		{
			dt = 0.0f;
			stopDt += static_cast<float>(AEFrameRateControllerGetFrameTime());
			if (stopDt > 2.f)
			{
				stopMain = false;
				player->stop = false;
				stopDt = 0.0f;
			}
		}

		UFO_dt += dt;
		idx_dt += dt;
		
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
		ColliderComponent* wbc = (ColliderComponent*)wBot->FindComponent("Collider");

		ColliderComponent* pc = (ColliderComponent*)player->FindComponent("Collider");
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

				float x = (W_WIDTH / 2) - abs(leftMost->GetPos().x) + 1.f;
	
				Octopus0[i]->SetPos(Octopus0[i]->GetPos().x + x, Octopus0[i]->GetPos().y - 20.f);
				Octopus1[i]->SetPos(Octopus1[i]->GetPos().x + x, Octopus1[i]->GetPos().y - 20.f);
				Crab0[i]->SetPos(Crab0[i]->GetPos().x + x, Crab0[i]->GetPos().y - 20.f);
				Crab1[i]->SetPos(Crab1[i]->GetPos().x + x, Crab1[i]->GetPos().y - 20.f);
				Squid[i]->SetPos(Squid[i]->GetPos().x + x, Squid[i]->GetPos().y - 20.f);
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

				float x = (W_WIDTH / 2) - abs(rightMost->GetPos().x) + 1.f;
			
				Octopus0[i]->SetPos(Octopus0[i]->GetPos().x - x, Octopus0[i]->GetPos().y - 20.f);
				Octopus1[i]->SetPos(Octopus1[i]->GetPos().x - x, Octopus1[i]->GetPos().y - 20.f);
				Crab0[i]->SetPos(Crab0[i]->GetPos().x - x, Crab0[i]->GetPos().y - 20.f);
				Crab1[i]->SetPos(Crab1[i]->GetPos().x - x, Crab1[i]->GetPos().y - 20.f);
				Squid[i]->SetPos(Squid[i]->GetPos().x - x, Squid[i]->GetPos().y - 20.f);
				move_dir = 1;
			}
		}

		//Move invaders
		if (UFO_dt > UFO->GetSpawnTime())
		{
			//std::cout << "!! UFO has spawned !! Spawn Time : " << UFO->GetSpawnTime() << ", POINTS : " << UFO->GetPoints() << std::endl;
			if (move_dir > 0)
				UFO->SetPos(W_WIDTH / 2 - 30.f, (W_HEIGHT / 2) - 100.f);
			else
				UFO->SetPos(-(W_WIDTH / 2) + 30.f, (W_HEIGHT / 2) - 100.f);

			UFO->SetSpeed(15.f * move_dir);
			UFO->alive = true;
			UFO->Visible(true);
			UFO->move = true;
			UFO->Sound(true);

			UFO->SetRandomSpawn();
			UFO->SetRandomPoints();
			UFO_dt = 0.0f;
		}

		ColliderComponent* uc = (ColliderComponent*)UFO->FindComponent("Collider");
		if (uc->IsCollision(lc) || uc->IsCollision(rc))
		{
			std::cout << "UFO collision" << std::endl;
			UFO->SetPos(0, -W_HEIGHT);
			UFO->Visible(false);
			UFO->move = false;
			UFO->alive = false;
			UFO->Sound(false);
		}

		//std::cout << "Left Invader : " << GetLiveInvaders() << std::endl;
		for (int i = 0; i < COL; i++)
		{
			float curSpeed = 100.f * move_dir;
			Octopus0[i]->SetSpeed(curSpeed);
			Octopus1[i]->SetSpeed(curSpeed);
			Crab0[i]->SetSpeed(curSpeed);
			Crab1[i]->SetSpeed(curSpeed);
			Squid[i]->SetSpeed(curSpeed);
		}

		if (GetLiveInvaders() < 3)
			_moveDt = 0.01f;
		else if (GetLiveInvaders() < 15)
			_moveDt = 0.1f;
		else if (GetLiveInvaders() < 25)
			_moveDt = 0.3f;
		else if (GetLiveInvaders() < 33)
			_moveDt = 0.5f;
		else if (GetLiveInvaders() < 50)
			_moveDt = 0.7f;
		else if (GetLiveInvaders() < 60)
			_moveDt = 0.9f;

		if (idx_dt > _moveDt)
		{
			UpdateDead();
			for (int i = 0; i < COL; i++)
			{
				Octopus0[i]->idx = (Octopus0[i]->idx + 1) % 2;
				Octopus0[i]->SetTexIndex(Octopus0[i]->idx);
				
				Octopus1[i]->idx = (Octopus1[i]->idx + 1) % 2;
				Octopus1[i]->SetTexIndex(Octopus1[i]->idx);
				
				Crab0[i]->idx = (Crab0[i]->idx + 1) % 2;
				Crab0[i]->SetTexIndex(Crab0[i]->idx);
				
			
				Crab1[i]->idx = (Crab1[i]->idx + 1) % 2;
				Crab1[i]->SetTexIndex(Crab0[i]->idx);
				
		
				Squid[i]->idx = (Squid[i]->idx + 1) % 2;
				Squid[i]->SetTexIndex(Squid[i]->idx);

				Octopus0[i]->Move(dt);
				Octopus1[i]->Move(dt);
				Crab0[i]->Move(dt);
				Crab1[i]->Move(dt);
				Squid[i]->Move(dt);
			}
			idx_dt = 0.f;
		}

		for (int i = 0; i < COL; i++)
			UFO->Move(dt);
	
		
		//Player Bullet
		ColliderComponent* bc = (ColliderComponent*)player->GetBullet()->FindComponent("Collider");
		if (player->GetBullet()->alive)
		{
			player->GetBullet()->SetSpeed(500.f);
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
					std::cout << "Bullet collision " << oc1->GetOwner()->GetID() << std::endl;
					player->GetBullet()->SetSpeed(0.f);
					player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
					player->GetBullet()->Dead();

					//Octopus0[i]->alive = false;
					Octopus0[i]->Dead();
					Octopus0[i]->SetTexIndex(2);

					score->AddPoint(Octopus0[i]->GetPoints());
					InvaderNum--;
					if (IsAttacker(Octopus0[i])) CurAttackNum--;
				}
				if (bc->IsCollision(oc2))
				{
					std::cout << "Bullet collision " << oc2->GetOwner()->GetID() << std::endl;
					player->GetBullet()->SetSpeed(0.f);
					player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
					player->GetBullet()->Dead();

					//Octopus1[i]->alive = false;
					Octopus1[i]->Dead();
					Octopus1[i]->SetTexIndex(2);

					score->AddPoint(Octopus1[i]->GetPoints());
					InvaderNum--;
					if (IsAttacker(Octopus1[i])) CurAttackNum--;
				}
				if (bc->IsCollision(cc1))
				{
					std::cout << "Bullet collision " << cc1->GetOwner()->GetID() << std::endl;
					player->GetBullet()->SetSpeed(0.f);
					player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
					player->GetBullet()->Dead();

					//Crab0[i]->alive = false;
					Crab0[i]->Dead();
					Crab0[i]->SetTexIndex(2);

					score->AddPoint(Crab0[i]->GetPoints());
					InvaderNum--;
					if (IsAttacker(Crab0[i])) CurAttackNum--;
				}
				if (bc->IsCollision(cc2))
				{
					std::cout << "Bullet collision " << cc2->GetOwner()->GetID() << std::endl;
					player->GetBullet()->SetSpeed(0.f);
					player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
					player->GetBullet()->Dead();

					//Crab1[i]->alive = false;
					Crab1[i]->Dead();
					Crab1[i]->SetTexIndex(2);
					
					score->AddPoint(Crab1[i]->GetPoints());
					InvaderNum--;
					if (IsAttacker(Crab1[i])) CurAttackNum--;
				}
				if (bc->IsCollision(sc))
				{
					std::cout << "Bullet collision " << sc->GetOwner()->GetID() << std::endl;
					player->GetBullet()->SetSpeed(0.f);
					player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
					player->GetBullet()->Dead();

					//Squid[i]->alive = false;
					Squid[i]->Dead();
					Squid[i]->SetTexIndex(2);

					score->AddPoint(Squid[i]->GetPoints());
					InvaderNum--;
					if (IsAttacker(Squid[i])) CurAttackNum--;
				}
				if (UFO->alive)
				{
					if (bc->IsCollision(uc))
					{
						player->GetBullet()->SetSpeed(0.f);
						player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
						player->GetBullet()->Dead();

						UFO->SetPos(0, -W_HEIGHT);
						UFO->Visible(false);
						UFO->move = false;
						UFO->alive = false;
						UFO->Sound(false);
						score->AddPoint(UFO->GetPoints());
					}
				}
			}
			score->SetStr();

			//Check Bullet Wall Collision : If Bullet hits the wall, the bullet is destroyed.
			if (bc->IsCollision(tc))
			{
				player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
				player->GetBullet()->Dead();
			}
		}

		//Invaders Attack
		for (int i = 0; i < COL; i++)
		{
			if (Attacker[i].first && Attacker[i].second)
			{
				ColliderComponent* obc = (ColliderComponent*)Attacker[i].first->GetBullet()->FindComponent("Collider");
				Attacker[i].first->attackDt += dt;
				if (Attacker[i].first->attackDt > Attacker[i].first->attackTime)
				{
					if (!Attacker[i].first->attack)
					{
						Attacker[i].first->attack = true;
						Attacker[i].first->Attack();
					}
					else
					{
						Attacker[i].first->GetBullet()->FromInvader(dt);
						if (obc->IsCollision(wbc))
						{
							Attacker[i].first->GetBullet()->SetPos(Attacker[i].first->GetPos().x, Attacker[i].first->GetPos().y - Attacker[i].first->GetSize().y / 2.f);
							Attacker[i].first->GetBullet()->Dead();
							Attacker[i].first->attack = false;
							Attacker[i].second = false;
							CurAttackNum--;
						}

						//Player - Invader Bullet Collision
						if (obc->IsCollision(pc))
						{ 
							Attacker[i].first->GetBullet()->SetPos(Attacker[i].first->GetPos().x, Attacker[i].first->GetPos().y - Attacker[i].first->GetSize().y / 2.f);
							Attacker[i].first->GetBullet()->Dead();
							Attacker[i].first->attack = false;
							Attacker[i].second = false;
							CurAttackNum--;

							player->LoseLife();
							Stop();
						}
					}
				}
				if (CurAttackNum > 0 && Attacker[i].second && Attacker[i].first->attackDt > 15.f)
				{
					Attacker[i].second = false;
					CurAttackNum = 0;
				}
			}
		}

		if (CurAttackNum == 0)
		{
			UpdateBottom();
			SetAttacker(2);
		}

		if (player->GetLife() < 1)
			GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GameOver);
		if(GetLiveInvaders() > 0)
		{
			if (GetBottom()->GetPos().y <= player->GetPos().y + player->GetSize().y)
				GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GameOver);
		}
	}
	else
		GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GoalLevel);
}

void Levels::MainLevel::Exit()
{
	AEAudioUnloadAudio(bgm);
	AEAudioUnloadAudioGroup(bgm_group);

	delete score;
	delete player;

	for (int i = 0; i < COL; i++)
	{
		delete Octopus0[i];
		delete Octopus1[i];
		delete Crab0[i];
		delete Crab1[i];
		delete Squid[i];
	}
	delete UFO;

	delete wLeft, wRight;
	delete wTop, wBot;

	AEGfxDestroyFont(fontName);
}
