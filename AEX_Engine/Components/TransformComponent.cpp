#include "TransformComponent.h"
#include <iostream>

void TransformComponent::CalculateMatrix()
{
	//Create a transtorm matrix
	AEMtx33 translateMtx;
	AEMtx33Trans(&translateMtx, pos.x, pos.y);
	
	//Create a Rotation matrix
	AEMtx33 rotationMtx;
	AEMtx33Rot(&rotationMtx, rot);

	//Create a scale matrix
	AEMtx33 scaleMtx;
	AEMtx33Scale(&scaleMtx, scale.x, scale.y);

	//Concatenate them
	AEMtx33Concat(&transformMatrix, &rotationMtx, &scaleMtx);
	AEMtx33Concat(&transformMatrix, &translateMtx, &transformMatrix);
}

TransformComponent::TransformComponent(GameObject* go) : EngineComponent(go), pos(), scale(), rot(0), transformMatrix()
{
	ID = "Transform";
	//EngineComponentManager* mgt = EngineComponentManager::getPtr();
	//mgt->AddEngine(this);

	pos.x = 0;
	pos.y = 0;

	scale.x = 1;
	scale.y = 1;

	CalculateMatrix();
}

void TransformComponent::Update()
{
	PrintMatrix();
}

void TransformComponent::SetPos(const AEVec2& otherPos)
{
	this->pos = otherPos;
	CalculateMatrix();
}

void TransformComponent::SetScale(const AEVec2& otherScale)
{
	this->scale = otherScale;
	CalculateMatrix();
}

void TransformComponent::SetRot(const float& otherRot)
{
	this->rot = otherRot;
	CalculateMatrix();
}

void TransformComponent::PrintMatrix()
{
	std::cout << "Printing Transform Comp. With this values : " << std::endl;
	std::cout << "Translate : " << pos.x << " " << pos.y << std::endl;
	std::cout << "   Rotate : " << rot << std::endl;
	std::cout << "    Scale : " << scale.x << " " << scale.y << std::endl;
	std::cout << "-----------------------------------\n";
	for (int i = 0; i < 3; i++)
	{
		std::cout << "|";
		for (int j = 0; j < 3; j++)
			std::cout << " " << transformMatrix.m[i][j];
		std::cout << "|\n";
	}
	std::cout << "-----------------------------------\n";
}
