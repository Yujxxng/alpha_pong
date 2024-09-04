#pragma once

#include "../Utils/myUtils.h"

#include "../ComponentManager/GameObject.h"

#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Object/Bullet.h"

class Life : public GameObject
{
	AEVec2 size{ 25.f, 20.f };
	AEVec2 pos;
	Color color;

public:
	~Life();

	void InitLife();
	void SetLife(std::string id, float sizeX, float sizeY, float posX, float posY, float r, float g, float b);
	void SetSize(float x, float y);
	void SetPos(float x, float y);
	void SetColor(float r, float g, float b);
	void SetTexture(std::string texName);

	AEVec2 GetSize() const { return size; }
	AEVec2 GetPos() const { return pos; }
	
	void Visible(bool);
};