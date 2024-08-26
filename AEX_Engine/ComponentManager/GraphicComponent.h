#pragma once
#include "BaseComponent.h"

using namespace std;

class GraphicComponent : public BaseComponent
{
public:
	GraphicComponent() = delete;
	GraphicComponent(GameObject* go);
	~GraphicComponent();

	GameObject* GetOwner();

	void Update() override;
};
