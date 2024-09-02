#pragma once

#include "../Utils/myUtils.h"

#include "../ComponentManager/GameObject.h"

#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AudioComponent.h"
#include "../Components/ColliderComponent.h"

#include "../ComponentManager/EventManager.h"

class Wall : public GameObject
{
	AEVec2 size;
	AEVec2 pos;
	Color color;

public:
	~Wall();

	void InitWall();
	void SetWall(std::string id, float sizeX, float sizeY, float posX, float posY, float r, float g, float b);
	void SetSize(float x, float y);
	void SetPos(float x, float y);
	void SetColor(float r, float g, float b);

	AEVec2 GetSize() const { return size; }
	AEVec2 GetPos() const { return pos; }

	void printInfo();
};