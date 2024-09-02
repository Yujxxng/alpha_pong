#pragma once

#include <string>
#include "AEEngine.h"
#include "../ComponentManager/GraphicComponent.h"
#include "../ComponentManager/GraphicComponentManager.h"
#include "../Utils/myUtils.h"

class Font : public GraphicComponent
{
private:
	std::string str;

	s8 fontID = -1;
	std::string fontName;

	AEVec2 pos{ 0.f, 0.f };
	float size{ 10.f };
	Color color{ 255, 255, 255 };

public:
	Font(GameObject* go);
	~Font();

	GameObject* GetOwner();

	void Update() override;

	Color& GetColor() { return color; }

	void SetPos(float x, float y) { pos = { x, y }; };
	void SetSize(float s) { size = s; }
	void SetColor(const Color& c) { color = c; }
	void SetFont(const std::string& name);
	void SetStr(std::string s) { str = s; }

	void LoadFromJson(const json&) override {};
	json SaveToJson() override;

	static ComponentSerializer* CreateComponent(GameObject* owner);
};