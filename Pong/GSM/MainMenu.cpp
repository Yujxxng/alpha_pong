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
#include "../Components/ColliderComponent.h"
#include "../ComponentManager/ResourceManager.h"

#include "../Object/Racket.h"
#include "../Object/Ball.h"
#include "../Object/Wall.h"

#include "../Event/BallWallCollisionEvent.h"

Wall *top, *bot;
Wall* wLeft, * wRight; //only for test

Racket* racket_L;
Racket* racket_R;
Ball* ball;

SomeEntity* entity;

float t = 0.0f;
int pX, pY;

void Levels::MainLevel::Init()
{
	AEGfxSetBackgroundColor(0.f, 0.f, 0.f);

	top = new Wall;
	top->InitWall();
	top->SetWall("top", W_WIDTH, 20.f, 0.f, (W_HEIGHT / 2) - 10.f, 0.f, 255.f, 255.f);
	
	bot = new Wall;
	bot->InitWall();
	bot->SetWall("bot", W_WIDTH, 20.f, 0.f, -(W_HEIGHT / 2) + 10.f, 0.f, 255.f, 255.f);

#if 1
	wLeft = new Wall;
	wLeft->InitWall();
	wLeft->SetWall("left", 20.f, W_HEIGHT, -(W_WIDTH / 2) + 10.f, 0.f, 0.f, 255.f, 255.f);

	wRight = new Wall;
	wRight->InitWall();
	wRight->SetWall("right", 20.f, W_HEIGHT, (W_WIDTH / 2) - 10.f, 0.f, 0.f, 255.f, 255.f);
#endif


	racket_L = new Racket;
	racket_L->InitRacket();
	racket_L->SetRacket("racketL", 15.f, 60.f, -550.f, 0.f, 255.f, 255.f, 255.f);
	PlayerComponent* p = (PlayerComponent*)racket_L->FindComponent("Player");
	p->AddKey("W");
	p->AddKey("S");
	ColliderComponent* c = (ColliderComponent*)racket_L->FindComponent("Collider");
	c->SetCollision(racket_L->GetPos().x, racket_L->GetPos().y, racket_L->GetSize().x, racket_L->GetSize().y);


	racket_R = new Racket;
	racket_R->InitRacket();
	racket_R->SetRacket("racketR", 15.f, 60.f, 550.f, 0.f, 255.f, 255.f, 255.f);
	p = (PlayerComponent*)racket_R->FindComponent("Player");
	p->AddKey("UP");
	p->AddKey("DOWN");
	c = (ColliderComponent*)racket_R->FindComponent("Collider");
	c->SetCollision(racket_R->GetPos().x, racket_R->GetPos().y, racket_R->GetSize().x, racket_R->GetSize().y);
	//racket_R->printInfo();
	

	ball = new Ball;
	ball->InitBall();
	ball->SetBall("ball", 15.f, 15.f, 0.f, 0.f, 255.f, 255.f, 255.f);
	ball->SetDirection();
	c = (ColliderComponent*)ball->FindComponent("Collider");
	c->SetCollision(ball->GetPos().x, ball->GetPos().y, ball->GetSize().x, ball->GetSize().y);
	//ball->printInfo();

	entity = new SomeEntity;
	EventManager::GetPtr()->RegisterEnt("BallWall", entity);
}

void Levels::MainLevel::Update()
{
	//time
	t = AEFrameRateControllerGetFrameTime();

	AEInputGetCursorPosition(&pX, &pY);
	//racket_R->SetPos(550.f, W_HEIGHT / 2 - pY);
	//ball->SetPos(pX - (W_WIDTH / 2), (W_HEIGHT / 2) - pY);
	//ball->SetDirection();
	
	//Update Objects Position
	TransformComponent* t = (TransformComponent*)racket_L->FindComponent("Transform");
	racket_L->SetPos(t->GetPos().x, t->GetPos().y);
	t = (TransformComponent*)racket_R->FindComponent("Transform");
	racket_R->SetPos(t->GetPos().x, t->GetPos().y);


	//std::cout << ball->GetPos().x << " , " << ball->GetPos().y << std::endl;
	//std::cout << racket_L->GetPos().x << " , " << racket_L->GetPos().y << std::endl;
	ColliderComponent* wtc = (ColliderComponent*)top->FindComponent("Collider");
	ColliderComponent* wbc = (ColliderComponent*)bot->FindComponent("Collider");
	ColliderComponent* wlc = (ColliderComponent*)wLeft->FindComponent("Collider");
	ColliderComponent* wrc = (ColliderComponent*)wRight->FindComponent("Collider");

	ColliderComponent* lc = (ColliderComponent*)racket_L->FindComponent("Collider");
	ColliderComponent* rc = (ColliderComponent*)racket_R->FindComponent("Collider");
	ColliderComponent* bc = (ColliderComponent*)ball->FindComponent("Collider");
	
	//Check Collision
	if (bc->IsCollision(lc))
	{
		racket_L->SetColor(100.f, 100.f, 100.f);
		ball->Stop();
		ball->cp = 2;
		ball->SetDirection();
	}
	else
		racket_L->SetColor(255.f, 255.f, 255.f);

	if (bc->IsCollision(rc))
	{
		racket_R->SetColor(100.f, 100.f, 100.f);
		ball->Stop();
		ball->cp = 3;
		ball->SetDirection();
	}
	else
		racket_R->SetColor(255.f, 255.f, 255.f);

	if (bc->IsCollision(wtc))
	{
		BallWallCollisionEvent* bwe = new BallWallCollisionEvent();
		bwe->ball = ball;
		bwe->wall = top;
		bwe->cp = 0;
		EventManager::GetPtr()->AddEvent(bwe);

		//top->SetColor(255.f, 0.f, 0.f);
		//ball->Stop();
		//ball->cp = 0;
		//ball->SetDirection();
	}
	else
		top->SetColor(0.f, 255.f, 255.f);

	if (bc->IsCollision(wbc))
	{
		BallWallCollisionEvent* bwe = new BallWallCollisionEvent();
		bwe->ball = ball;
		bwe->wall = bot;
		bwe->cp = 1;
		EventManager::GetPtr()->AddEvent(bwe);
		//bot->SetColor(255.f, 0.f, 0.f);
		//ball->Stop();
		//ball->cp = 1;
		//ball->SetDirection();
	}
	else
		bot->SetColor(0.f, 255.f, 255.f);

#if 0
	if (bc->IsCollision(wlc))
	{
		wLeft->SetColor(255.f, 0.f, 0.f);
		ball->Stop();
		ball->cp = 2;
		ball->SetDirection();
	}
	else
		wLeft->SetColor(0.f, 255.f, 255.f);

	if (bc->IsCollision(wrc))
	{
		wRight->SetColor(255.f, 0.f, 0.f);
		ball->Stop();
		ball->cp = 3;
		ball->SetDirection();
	}
	else
		wRight->SetColor(0.f, 255.f, 255.f);
#endif
	ball->Move(::t);


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
	delete racket_L;
	delete racket_R;
	delete ball;
	delete top;
	delete bot;
}
