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

Racket* racket_L;
Racket* racket_R;
Ball* ball;

int pX, pY;
void Levels::MainLevel::Init()
{
	AEGfxSetBackgroundColor(0.f, 0.f, 0.f);
	
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
	c = (ColliderComponent*)ball->FindComponent("Collider");
	c->SetCollision(ball->GetPos().x, ball->GetPos().y, ball->GetSize().x, ball->GetSize().y);
	//ball->printInfo();
}

void Levels::MainLevel::Update()
{
	//Update Objects Position
	AEInputGetCursorPosition(&pX, &pY);

	//racket_R->SetPos(550.f, W_HEIGHT / 2 - pY);
	ball->SetPos(pX - (W_WIDTH / 2), (W_HEIGHT / 2) - pY);
	TransformComponent* t = (TransformComponent*)racket_L->FindComponent("Transform");
	racket_L->SetPos(t->GetPos().x, t->GetPos().y);
	t = (TransformComponent*)racket_R->FindComponent("Transform");
	racket_R->SetPos(t->GetPos().x, t->GetPos().y);


	//std::cout << ball->GetPos().x << " , " << ball->GetPos().y << std::endl;
	//std::cout << racket_L->GetPos().x << " , " << racket_L->GetPos().y << std::endl;
	ColliderComponent* lc = (ColliderComponent*)racket_L->FindComponent("Collider");
	ColliderComponent* rc = (ColliderComponent*)racket_R->FindComponent("Collider");
	ColliderComponent* bc = (ColliderComponent*)ball->FindComponent("Collider");
	
	//Check Collision
	//if (lc->IsCollision(bc) || rc->IsCollision(bc))
	if (bc->IsCollision(lc) || bc->IsCollision(rc))
		std::cout << "cccccccccccccccccccccc" << std::endl;
	else
		std::cout << "nnnnnn" << std::endl;

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
}
