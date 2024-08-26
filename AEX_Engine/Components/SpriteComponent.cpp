#include "SpriteComponent.h"
#include <iostream>

#include "../ComponentManager/GameObject.h"
#include "../ComponentManager/EngineComponent.h"
#include "TransformComponent.h"


SpriteComponent::SpriteComponent(GameObject* go) : GraphicComponent(go)
{
	ID = "Sprite";
}

SpriteComponent::~SpriteComponent()
{
	AEGfxTextureUnload(mTex);
}

void SpriteComponent::Update()
{
	//if (BaseComponent::Update() == false) return false;
#if 0
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0, 1,
		0.5f, -0.5f, 0xFFFFFFFF, 1, 1,
		-0.5f, 0.5f, 0xFFFFFFFF, 0, 0
	);
	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1, 1,
		0.5f, 0.5f, 0xFFFFFFFF, 1, 0,
		-0.5f, 0.5f, 0xFFFFFFFF, 0, 0
	);

	AEGfxVertexList* mesh = AEGfxMeshEnd();

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	//AEGfxSetColorToMultiply(mColor.r / 255.f, mColor.g / 255.f, mColor.b / 255.f, 255.f);

	AEGfxSetColorToMultiply(1, 1, 1, 1);
	//AEGfxSetColorToAdd(1, 0, 0, 0);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	AEGfxTextureSet(mTex, 0, 0);

	TransformComponent* trs = (TransformComponent*)owner->FindComponent("Transform");
	AEMtx33 tranf = trs->getMatrix();
	
	AEGfxSetTransform(tranf.m);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	AEGfxMeshFree(mesh);
#elif 1
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxVertexList* mesh = AEGfxMeshEnd();

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	//AEGfxSetColorToMultiply(mColor.r / 255.f, mColor.g / 255.f, mColor.b / 255.f, 255.f);

	AEGfxSetColorToMultiply(1, 1, 1, 1);
	//AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
	AEGfxSetColorToAdd(mColor.r / 255.f, mColor.g / 255.f, mColor.b / 255.f, 0);
	
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

	AEGfxTextureSet(mTex, 0, 0);

	TransformComponent* trs = (TransformComponent*)owner->FindComponent("Transform");
	AEMtx33 tranf = trs->getMatrix();
	AEGfxSetTransform(tranf.m);

	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	AEGfxMeshFree(mesh);

#endif
}

void SpriteComponent::SetTexture(std::string s)
{
	if (mTex != nullptr)
		AEGfxTextureUnload(mTex);

	mTex = AEGfxTextureLoad(s.c_str());
}

