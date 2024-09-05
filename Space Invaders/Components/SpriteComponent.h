#pragma once

#include "..\ComponentManager\/GraphicComponent.h"
#include "..\ComponentManager\/GraphicComponentManager.h"
#include "../Utils/myUtils.h"

#include "AEEngine.h"
#include "AEGraphics.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class SpriteComponent : public GraphicComponent
{
private:
	Color mColor{};
	float alpha{ 255.f };

	//AEGfxTexture* mTex = nullptr;
	//std::string texName;

	std::vector<AEGfxTexture*> mTex;
	std::vector<std::string> texName;

	int texNum = 0;
public:
	int index = 0;

public:
	SpriteComponent(GameObject* go);
	~SpriteComponent();

	GameObject* GetOwner();

	void Update() override;

	Color& GetColor() { return mColor; }

	void SetColor(const Color&);
	void SetAlpha(float);
	void SetTexture(std::string s);
	bool FindTextureName(std::string name);

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static ComponentSerializer* CreateComponent(GameObject* owner);
};
