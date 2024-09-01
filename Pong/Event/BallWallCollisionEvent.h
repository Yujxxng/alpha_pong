#pragma once
#include "Event.h"
#include "../Object/Ball.h"
#include "../Object/Wall.h"
#include "../Object/Score.h"

class BallWallCollisionEvent : public Event //custom event
{
public:
	BallWallCollisionEvent();
	~BallWallCollisionEvent() {};

	Wall* wall;
	Ball* ball;
	
	int cp = -1;
};

class BallOutEvent : public Event
{
public:
	BallOutEvent();
	~BallOutEvent() {};

	Wall* wall;
	Ball* ball;
	Score* score;
};

class SomeEntity : public Entity
{
public:
	void OnEvent(Event*) override;
};