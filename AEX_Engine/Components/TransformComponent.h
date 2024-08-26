#pragma once
#include "..\ComponentManager\/EngineComponentManager.h"
#include "..\ComponentManager\/EngineComponent.h"
#include <string>

#include "AEMath.h"

using namespace std;

class TransformComponent : public EngineComponent
{
	AEVec2 pos;
	AEVec2 scale;
	float rot;

	AEMtx33 transformMatrix;

	void CalculateMatrix();
public:
	TransformComponent(GameObject* go);

	GameObject* GetOwner();

	void Update() override;

	//Getters
	const AEVec2& GetPos() const { return pos; }
	const AEVec2& GetScale() const { return scale; }
	const float& GetRot() const { return rot; }
	const AEMtx33& getMatrix() const { return transformMatrix; }

	//Mutators
	void SetPos(const AEVec2& otherPos);
	void SetScale(const AEVec2& otherScale);
	void SetRot(const float& otherRot);

	void PrintMatrix();
};
