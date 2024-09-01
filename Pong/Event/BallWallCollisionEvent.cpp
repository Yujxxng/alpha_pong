#include "BallWallCollisionEvent.h"

BallWallCollisionEvent::BallWallCollisionEvent()
{
	id = "BallWall";
}

BallOutEvent::BallOutEvent()
{
	id = "BallOut";
}

void SomeEntity::OnEvent(Event* event)
{
	if (event->getID() == "BallWall")
	{
		//top->SetColor(255.f, 0.f, 0.f);
		//ball->Stop();
		//ball->cp = 0;
		//ball->SetDirection();

		BallWallCollisionEvent* e = (BallWallCollisionEvent*)event;
		e->wall->SetColor(255.f, 0.f, 0.f);
		e->ball->Stop();
		e->ball->cp = e->cp;
		e->ball->SetDirection();
	}

	else if (event->getID() == "BallOut")
	{
		BallOutEvent* e = (BallOutEvent*)event;
		e->ball->SetPosCenter();
		e->ball->cp = -1;

		e->score->AddPoint();
		e->score->SetStr();
	}
}


