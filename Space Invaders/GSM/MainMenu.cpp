#include "MainMenu.h"
#include "GameStateManager.h"
#include "GoalLevel.h"
#include "GameOver.h"

#include <iostream>

#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../Resource/TextureResource.h"

#include "../ComponentManager/GameObject.h"
#include "../ComponentManager/EventManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"

int TotalScore = 0;

bool stopMain = false;

float dt = 0.0f;
float stopDt = 0.0f;
float _moveDt = 1.f;

float UFO_dt = 0.0f;
float idx_dt = 0.0f;

s8 fontName;
AEAudio bgm;
AEAudioGroup bgm_group;

Levels::MainLevel::~MainLevel()
{
	std::cout << __FUNCTION__ << std::endl;
}

void Levels::MainLevel::Init()
{
	std::cout << __FUNCTION__ << std::endl;
	//std::cout << "Main level Init:" << std::endl;
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	fontName = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();
	bgm_group = AEAudioCreateGroup();
	bgm = *(ResourceManager::GetPtr()->Get<AudioResource>("Assets/space_invaders/Invader Homeworld.mp3")->GetData());
	AEAudioPlay(bgm, bgm_group, 0.5f, 1.f, -1);

	//Init Score
	score = new Score;
	score->InitScore();
	score->SetScore("score", 0.8f, 0.f, 0.80f, 255.f, 255.f, 255.f);

	bulletMgt.InitBulletManager();

	//Init Player
	//player = new Player;
	//player->InitPlayer();
	//player->SetPlayer("player", 25.f, 20.f, 0.f, -200.f, 0.f, 255.f, 0.f);

	//Init Invaders
	//invaderMgt.InitInvaders();
	//invaderMgt.InitAttacker();

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


void Levels::MainLevel::Update()
{
	AEGfxPrint(fontName, "<SCORE>", -0.26f, 0.87f, 0.7f, 1.f, 1.f, 1.f, 1.f);
	
	AEGfxPrint(fontName, "LIFE : ", 0.5f, 0.915f, 0.5f, 1.f, 1.f, 1.f, 1.f);
	/*
	if (invaderMgt.GetLiveInvaders() > 0)
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
		ColliderComponent* leftMost = (ColliderComponent*)invaderMgt.GetLeft()->FindComponent("Collider");
		ColliderComponent* rightMost = (ColliderComponent*)invaderMgt.GetRight()->FindComponent("Collider");

		//Wall collider
		ColliderComponent* lc = (ColliderComponent*)wLeft->FindComponent("Collider");
		ColliderComponent* rc = (ColliderComponent*)wRight->FindComponent("Collider");
		ColliderComponent* tc = (ColliderComponent*)wTop->FindComponent("Collider");
		ColliderComponent* wbc = (ColliderComponent*)wBot->FindComponent("Collider");

		ColliderComponent* pc = (ColliderComponent*)player->FindComponent("Collider");

		//Check Wall Invaders Collision
		if (leftMost->IsCollision(lc))
		{
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					float x = (W_WIDTH / 2) - abs(leftMost->GetPos().x) + 1.f;
					invaderMgt.invaders[i][j].SetSpeed(0.f);
					invaderMgt.invaders[i][j].SetPos(invaderMgt.invaders[i][j].GetPos().x + x, invaderMgt.invaders[i][j].GetPos().y - 20.f);
					invaderMgt.move_dir = -1;
				}
			}
		}

		if (rightMost->IsCollision(rc))
		{
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					float x = (W_WIDTH / 2) - abs(rightMost->GetPos().x) + 1.f;
					invaderMgt.invaders[i][j].SetSpeed(0.f);
					invaderMgt.invaders[i][j].SetPos(invaderMgt.invaders[i][j].GetPos().x - x, invaderMgt.invaders[i][j].GetPos().y - 20.f);
					invaderMgt.move_dir = 1;
				}
			}
		}

		//Move invaders
		if (UFO_dt > invaderMgt.UFO->GetSpawnTime())
		{
			//std::cout << "!! UFO has spawned !! Spawn Time : " << UFO->GetSpawnTime() << ", POINTS : " << UFO->GetPoints() << std::endl;
			if (invaderMgt.move_dir > 0)
				invaderMgt.UFO->SetPos(W_WIDTH / 2 - 30.f, (W_HEIGHT / 2) - 100.f);
			else
				invaderMgt.UFO->SetPos(-(W_WIDTH / 2) + 30.f, (W_HEIGHT / 2) - 100.f);

			invaderMgt.UFO->SetSpeed(15.f * invaderMgt.move_dir);
			invaderMgt.UFO->alive = true;
			invaderMgt.UFO->Visible(true);
			invaderMgt.UFO->move = true;
			invaderMgt.UFO->Sound(true);

			invaderMgt.UFO->SetRandomSpawn();
			invaderMgt.UFO->SetRandomPoints();
			UFO_dt = 0.0f;
		}

		ColliderComponent* uc = (ColliderComponent*)invaderMgt.UFO->FindComponent("Collider");
		if (uc->IsCollision(lc) || uc->IsCollision(rc))
		{
			//std::cout << "UFO collision" << std::endl;
			invaderMgt.UFO->SetPos(0, -W_HEIGHT);
			invaderMgt.UFO->Visible(false);
			invaderMgt.UFO->move = false;
			invaderMgt.UFO->alive = false;
			invaderMgt.UFO->Sound(false);
		}

		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				float curSpeed = 100.f * invaderMgt.move_dir;
				invaderMgt.invaders[i][j].SetSpeed(curSpeed);
			}
		}

		//Set the speed according to the alive invaders.

		if (invaderMgt.GetLiveInvaders() < 2)
			_moveDt = 0.01f;
		else if (invaderMgt.GetLiveInvaders() < 4)
			_moveDt = 0.03f;
		else if (invaderMgt.GetLiveInvaders() < 8)
			_moveDt = 0.05f;
		else if (invaderMgt.GetLiveInvaders() < 12)
			_moveDt = 0.1f;
		else if (invaderMgt.GetLiveInvaders() < 22)
			_moveDt = 0.3f;
		else if (invaderMgt.GetLiveInvaders() < 40)
			_moveDt = 0.5f;
		else if (invaderMgt.GetLiveInvaders() < 50)
			_moveDt = 0.9f;

		if (idx_dt > _moveDt)
		{
			invaderMgt.UpdateDead();
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					invaderMgt.invaders[i][j].idx = (invaderMgt.invaders[i][j].idx + 1) % 2;
					invaderMgt.invaders[i][j].SetTexIndex(invaderMgt.invaders[i][j].idx);

					invaderMgt.invaders[i][j].Move(dt);
				}
			}
			idx_dt = 0.f;
		}

		for (int i = 0; i < COL; i++)
			invaderMgt.UFO->Move(dt);
	
		//Player Bullet
		ColliderComponent* bc = (ColliderComponent*)player->GetBullet()->FindComponent("Collider");
		if (player->GetBullet()->alive)
		{
			player->GetBullet()->SetSpeed(500.f);
			player->GetBullet()->Fly(dt);
			
			//Check Bullet Invaders Collision : If Collision is true -> The invader is dead.
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					ColliderComponent* ic = (ColliderComponent*)invaderMgt.invaders[i][j].FindComponent("Collider");
					if (bc->IsCollision(ic) && invaderMgt.invaders[i][j].alive)
					{
						player->GetBullet()->SetSpeed(0.f);
						player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
						player->GetBullet()->Dead();

						invaderMgt.invaders[i][j].alive = false;
						invaderMgt.invaders[i][j].SetTexIndex(2);

						score->AddPoint(invaderMgt.invaders[i][j].GetPoints());
						//std::cout << invaderMgt.invaders[i][j].GetID() << " : " << invaderMgt.invaders[i][j].GetPoints() << std::endl;
						invaderMgt.InvaderNum--;
						//if (invaderMgt.IsAttacker(&invaderMgt.invaders[i][j]))
						//	invaderMgt.CurAttackNum--;
					}
				}
			}
			if (invaderMgt.UFO->alive)
			{
				if (bc->IsCollision(uc))
				{
					player->GetBullet()->SetSpeed(0.f);
					player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
					player->GetBullet()->Dead();

					invaderMgt.UFO->SetPos(0, -W_HEIGHT);
					invaderMgt.UFO->Visible(false);
					invaderMgt.UFO->move = false;
					invaderMgt.UFO->alive = false;
					invaderMgt.UFO->Sound(false);
					score->AddPoint(invaderMgt.UFO->GetPoints());
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

		//Invader Attack
		//invaderMgt.UpdateBottom();
		if (bulletMgt.GetBullet() != nullptr)
		{
			Bullet* bullet = bulletMgt.GetBullet();
			//std::cout << bullet->GetID() << std::endl;
			int attacker = invaderMgt.SetAttacker();
			if (invaderMgt.Attacker[attacker].first != nullptr)
			{
				invaderMgt.Attacker[attacker].second = true;
				//invaderMgt.Attacker[attacker].first->attack = true;

				AEVec2 pos = invaderMgt.Attacker[attacker].first->GetPos();
				bullet->alive = true;
				bullet->collision = false;
				bullet->SetMissileRandom();
				bullet->SetRandomSpeed();
				bullet->SetPos(pos.x, pos.y);
				bullet->Visible(true);
				invaderMgt.Attacker[attacker].first->SetBullet(bullet);
			}
		}

		bulletMgt.UpdateBullet(dt);

		//Player - Invader Bullet Collision
		for (auto& b : bulletMgt.pool)
		{
			if (b->alive)
			{
				ColliderComponent* abc = (ColliderComponent*)b->FindComponent("Collider");
				if (abc->IsCollision(pc))
				{
					b->SetPos(0, 0);
					b->Dead();
					b->collision = true;
				}

				if (b->collision)
				{
					b->collision = false;

					player->LoseLife();
					Stop();
				}
			}
		}
		for (int i = 0; i < COL; i++)
		{
			if (invaderMgt.Attacker[i].first != nullptr && invaderMgt.Attacker[i].second)
			{
				if (invaderMgt.Attacker[i].first->GetBullet() == nullptr)
					break;

				if (!invaderMgt.Attacker[i].first->GetBullet()->alive)
				{
					invaderMgt.Attacker[i].first->SetBullet(nullptr);
					invaderMgt.Attacker[i].second = false;
				}
			}
		}

		if (player->GetLife() < 1)
			0;// GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GameOver);

		else if(invaderMgt.GetLiveInvaders() > 0)
		{
			if (invaderMgt.GetBottom()->GetPos().y <= player->GetPos().y + player->GetSize().y)
				0;// GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GameOver);
		}
	}
	else
		0;// GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GoalLevel);
		*/
	
}

void Levels::MainLevel::Exit()
{
	std::cout << __FUNCTION__ << std::endl;
	//TotalScore = score->getPoint();

	//AEAudioUnloadAudio(bgm);
	AEAudioUnloadAudioGroup(bgm_group);

	delete score;
	delete player;

	//invaderMgt.deleteInvaders();

	delete wLeft;
	delete wRight;
	delete wTop;
	delete wBot;
	//AEGfxDestroyFont(fontName);
}
