#pragma once

#include "../Utils/myUtils.h"

#include "../ComponentManager/GameObject.h"

#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"

#include "../ComponentManager/EventManager.h"

class Racket : protected GameObject
{
	AEVec2 size;
	AEVec2 pos;
	Color color;

public:
	~Racket();

	void InitRacket();

	void SetRacketID(std::string);
	void SetSize(float x, float y);
	void SetPos(float x, float y);
	void SetColor(float r, float g, float b);

	void DrawRacket();
};