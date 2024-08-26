#pragma once
#include "..\ComponentManager\/GraphicComponent.h"
#include "..\ComponentManager\/GraphicComponentManager.h"

#include "AEEngine.h"
#include "AEGraphics.h"

#include <string>


using namespace std;

class SpriteComponent : public GraphicComponent
{
public:
	struct Color
	{
		unsigned char r = 255;
		unsigned char g = 0;
		unsigned char b = 0;
	};

private:
	Color mColor;
	AEGfxTexture* mTex = nullptr;

public:
	SpriteComponent(GameObject* go);
	~SpriteComponent();

	GameObject* GetOwner();

	void Update() override;

	Color& GetColor() { return mColor; }

	void SetTexture(std::string s);
};
