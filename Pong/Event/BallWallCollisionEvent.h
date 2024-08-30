#pragma once
#include "Event.h"
#include "../Object/Ball.h"
#include "../Object/Wall.h"

class BallWallCollisionEvent : public Event //custom event
{
public:
	BallWallCollisionEvent();
	~BallWallCollisionEvent();

	Wall* wall;
	Ball* ball;
	
	int cp = -1;
};

class SomeEntity : public Entity
{
public:
	void OnEvent(Event*) override;
};