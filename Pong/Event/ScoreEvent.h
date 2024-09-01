#pragma once
#include "Event.h"
#include "../Object/Ball.h"
#include "../Object/Wall.h"
#include "../Object/Score.h"

class GameOverEvent : public Event //custom event
{
public:
	GameOverEvent();
	~GameOverEvent() {};

	Score* L, * R;
	Ball* ball;
};

class GameResetEvent : public Event
{
public:
	GameResetEvent();
	~GameResetEvent() {};

	Score* L, * R;
	Ball* ball;
};

class ScoreEntity : public Entity
{
public:
	void OnEvent(Event*) override;
};