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
int HighScore = 0;
bool RankedIn = false;

bool stopMain = false;

//~dt~
float dt = 0.0f;
float _stopDt = 2.0f;
float _moveDt = 1.f;
float _deadDt = 0.4f;

float stop_dt = 0.0f;
float UFO_dt = 0.0f;
float idx_dt = 0.0f;
float bgm_dt = 0.0f;
float dead_dt = 0.0f;

s8 fontName;

int bgmIdx = 0;
AEAudio bgm[4];
AEAudio deadSound;
AEAudio killSound;
AEAudioGroup bgm_group;

Levels::MainLevel::~MainLevel()
{
}

void Levels::MainLevel::Init()
{
	RankedIn = false;
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	fontName = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();
	bgm_group = AEAudioCreateGroup();
	for (int i = 0; i < 4; i++)
	{
		std::string bgmName = "Assets/space_invaders/sounds/fastinvader";
		bgmName = bgmName + to_string(i) + ".mp3";
		bgm[i] = *(ResourceManager::GetPtr()->Get<AudioResource>(bgmName)->GetData());
	}
	deadSound = *(ResourceManager::GetPtr()->Get<AudioResource>("Assets/space_invaders/sounds/explosion.mp3")->GetData());
	killSound = *(ResourceManager::GetPtr()->Get<AudioResource>("Assets/space_invaders/sounds/invaderkilled.mp3")->GetData());

	dt = 0.0f;
	_moveDt = 1.f;
	_deadDt = 0.4f;

	stop_dt = 0.0f;
	UFO_dt = 0.0f;
	idx_dt = 0.0f;
	bgm_dt = 0.0f;
	dead_dt = 0.0f;

	//Init Score
	score = Score::getPtr();
	score->SetScore(0);
	if (score->getList().empty())
		score->LoadRankFromJson();
	HighScore = score->GetTopScore();

	bulletMgt.InitBulletManager();

	//Init Player
	player = new Player;
	player->InitPlayer();
	player->SetPlayer("player", 25.f, 20.f, 0.f, -200.f, 0.f, 255.f, 0.f);

	//Init Invaders
	invaderMgt.InitInvaders();
	invaderMgt.InitAttacker();

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

void Levels::MainLevel::ReLoad()
{
	invaderMgt.Stage = invaderMgt.Stage + 1;

	//set bullet
	dt = 0.0f;
	_moveDt = 1.f;

	stop_dt = 0.0f;
	UFO_dt = 0.0f;
	idx_dt = 0.0f;
	bgm_dt = 0.0f;
	dead_dt = 0.0f;

	invaderMgt.ResetInvaders();
	invaderMgt.InitAttacker();

	if (bulletMgt.poolSize > invaderMgt.AttackerNum)
	{
		if(invaderMgt.Stage % 2 == 0)
			invaderMgt.AttackerNum++;
	}

	if(player->GetLife() < 3)
		player->AddLife();
	player->SetPos(0.f, -200.f);
}

void Levels::MainLevel::Stop(float t)
{
	_stopDt = t;
	stopMain = true;
	player->stop = true;
}


void Levels::MainLevel::Update()
{
	if (AEInputCheckTriggered(AEVK_RBUTTON))
		ReLoad();

	f32 width, height;
	AEGfxGetPrintSize(fontName, "<SCORE>", 0.8f, &width, &height);
	AEGfxPrint(fontName, "<SCORE>", -width / 2, -height / 2 + 0.925f, 0.8f, 1.f, 1.f, 1.f, 1.f);
	score->Update();

	AEGfxPrint(fontName, "LIFE : ", 0.5f, 0.915f, 0.5f, 1.f, 1.f, 1.f, 1.f);
	AEGfxPrint(fontName, "HI-SCORE", -0.9f, 0.915f, 0.5f, 1.f, 1.f, 1.f, 1.f);

	if (score->getPoint() > HighScore)
		HighScore = score->getPoint();

	AEGfxPrint(fontName, to_string(HighScore).c_str(), -0.8f, 0.85f, 0.5f, 1.f, 1.f, 1.f, 1.f);
	
	if(!stopMain)
		dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
	else
	{
		dt = 0.0f;
		stop_dt += static_cast<float>(AEFrameRateControllerGetFrameTime());
		if (stop_dt > _stopDt)
		{
			stopMain = false;
			player->stop = false;
			stop_dt = 0.0f;
		}
	}
	if (invaderMgt.GetLiveInvaders() > 0)
	{

		UFO_dt += dt;
		idx_dt += dt;
		bgm_dt += dt;
		dead_dt += dt;

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
		//ColliderComponent* wbc = (ColliderComponent*)wBot->FindComponent("Collider");

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
			if (invaderMgt.move_dir > 0)
				invaderMgt.UFO->SetPos(W_WIDTH / 2 - 30.f, (W_HEIGHT / 2) - 100.f);
			else
				invaderMgt.UFO->SetPos(-(W_WIDTH / 2) + 30.f, (W_HEIGHT / 2) - 100.f);

			invaderMgt.UFO->SetSpeed(80.f * invaderMgt.move_dir);
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
			invaderMgt.UFO->SetPos(0, -W_HEIGHT);
			invaderMgt.UFO->Visible(false);
			invaderMgt.UFO->move = false;
			invaderMgt.UFO->alive = false;
			invaderMgt.UFO->Sound(false);
		}

		//Set Invaders direction
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

		if (_moveDt > 0.1f)
		{
			if (bgm_dt > _moveDt)
			{
				AEAudioPlay(bgm[bgmIdx], bgm_group, 1.0f, 1.f, 0);
				bgmIdx = (bgmIdx + 1) % 4;
				bgm_dt = 0.f;
			}
		}
		else
		{
			if (bgm_dt > _moveDt + 0.2f)
			{
				AEAudioPlay(bgm[bgmIdx], bgm_group, 1.0f, 1.f, 0);
				bgmIdx = (bgmIdx + 1) % 4;
				bgm_dt = 0.f;
			}
		}

		//Update Deads unvisiable
		if (dead_dt > _deadDt)
		{
			invaderMgt.UpdateDead();
			dead_dt = 0.0f;
		}

		//Move invaders and Update animation
		if (idx_dt > _moveDt)
		{
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					if (invaderMgt.invaders[i][j].alive)
						invaderMgt.invaders[i][j].SetTexIndex((invaderMgt.invaders[i][j].GetTexIndex() + 1) % 2);
					
					invaderMgt.invaders[i][j].Move(dt);
				}
			}
			idx_dt = 0.f;
		}
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

						AEAudioPlay(killSound, bgm_group, 0.1f, 1.f, 0);
						invaderMgt.invaders[i][j].alive = false;
						invaderMgt.invaders[i][j].SetTexIndex(2);

						score->AddPoint(invaderMgt.invaders[i][j].GetPoints());
						invaderMgt.InvaderNum--;
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
			//Check Bullet Wall Collision : If Bullet hits the wall, the bullet is destroyed.
			if (bc->IsCollision(tc))
			{
				player->GetBullet()->SetPos(player->GetPos().x, player->GetPos().y + player->GetSize().y / 2.f);
				player->GetBullet()->Dead();
			}
		}

		//Invader Attack
		if (bulletMgt.GetBullet() != nullptr && bulletMgt.GetAliveBullet() < invaderMgt.AttackerNum)
		{
			Bullet* bullet = bulletMgt.GetBullet();
			int attacker = invaderMgt.SetAttacker();
			if (invaderMgt.Attacker[attacker].first != nullptr)
			{
				invaderMgt.Attacker[attacker].second = true;

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

					AEAudioPlay(deadSound, bgm_group, 0.4f, 1.f, 0);
					player->LoseLife();
					bulletMgt.DeadBullets();
					Stop(2.0f);
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
			GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GameOver);

		else if(invaderMgt.Stage >= 5)
			GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GoalLevel);

		else if(invaderMgt.GetLiveInvaders() > 0)
		{
			if (invaderMgt.GetBottom()->GetPos().y <= player->GetPos().y + player->GetSize().y)
				GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new GameOver);
		}
	}
	else
	{
		//stop and print stage number
		Stop(2.0f);
		ReLoad();
		bulletMgt.DeadBullets();
		player->GetBullet()->Dead();
	}
}

void Levels::MainLevel::Exit()
{
	TotalScore = score->getPoint();

	if (TotalScore >= HighScore)
		HighScore = TotalScore;
	
	if(GSM::GameStateManager::GetGSMPtr()->gGameRunning != 0)
	{
		if (score->getRankSize() < 5)
			RankedIn = true;
		else
		{
			if (score->GetLowerScore() < TotalScore)
				RankedIn = true;
		}
	}

	if (invaderMgt.UFO->alive)
		invaderMgt.UFO->Sound(false);
	
	AEAudioUnloadAudioGroup(bgm_group);

	delete player;

	invaderMgt.deleteInvaders();

	delete wLeft;
	delete wRight;
	delete wTop;
	delete wBot;
}
