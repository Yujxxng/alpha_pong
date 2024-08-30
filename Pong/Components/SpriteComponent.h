#pragma once

#include "../ComponentManager/GraphicComponent.h"

#include "../Utils/myUtils.h"

#include "AEEngine.h"
#include "AEGraphics.h"

#include <string>

class SpriteComponent : public GraphicComponent
{
private:
	Color mColor = { 255, 0, 0 };

	AEGfxTexture* mTex = nullptr;
	std::string texName;

public:
	SpriteComponent(GameObject* go);
	~SpriteComponent();

	GameObject* GetOwner();

	void Update() override;

	Color& GetColor() { return mColor; }

	void SetColor(const Color&);
	void SetTexture(std::string s);

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static ComponentSerializer* CreateComponent(GameObject* owner);
};
