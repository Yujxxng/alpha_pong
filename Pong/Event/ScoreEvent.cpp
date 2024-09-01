#include "ScoreEvent.h"

GameOverEvent::GameOverEvent()
{
	id = "GameOverEvent";
}

GameResetEvent::GameResetEvent()
{
	id = "GameResetEvent";
}

void ScoreEntity::OnEvent(Event* event)
{
	if (event->getID() == "GameOverEvent")
	{
		GameOverEvent* e = (GameOverEvent*)event;

		e->ball->SetPosCenter();
	}

	else if (event->getID() == "GameResetEvent")
	{
		GameResetEvent* e = (GameResetEvent*)event;
		e->L->Reset();
		e->L->SetStr();
		e->R->Reset();
		e->R->SetStr();
		e->ball->SetPosCenter();
	}
}


