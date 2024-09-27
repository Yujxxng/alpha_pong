#include "Button.h"

#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../Resource/TextureResource.h"

#include <AEMath.h>

Button::Button()
{
	font = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();

	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	mesh = AEGfxMeshEnd();
}

Button::~Button()
{
	AEGfxMeshFree(mesh);
}

void Button::Update()
{
	DrawButton();
	DrawButtonText();
}

void Button::DrawButton()
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetColorToMultiply(color.r, color.g, color.b, 0);
	AEGfxSetColorToAdd(0, 0, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, size.x, size.y);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, pos.x, pos.y);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetTransform(transform.m);

	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void Button::DrawButtonText()
{
	f32 width, height;
	AEGfxGetPrintSize(font, text.c_str(), textSize, &width, &height);

	float x = pos.x * 2.f / AEGfxGetWindowWidth();
	float y = pos.y * 2.f / AEGfxGetWindowHeight();
	AEGfxPrint(font, text.c_str(), x - (width / 2), y - (height / 2), textSize, textColor.r, textColor.g, textColor.b, 1);
}

void Button::SetPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Button::SetText(std::string txt)
{
	text = txt;

	f32 width = 0, height = 0;
	AEGfxGetPrintSize(font, text.c_str(), textSize, &width, &height);

	size.x = AEGfxGetWindowWidth() * width / 2.f;
	size.y = AEGfxGetWindowHeight() * height / 2.f;
}

void Button::SetTextColor(unsigned char r, unsigned char g, unsigned char b)
{
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;
}

bool Button::isCollision(s32 x, s32 y)
{
	float my_leftX = pos.x - (size.x / 2.f);
	float my_leftY = pos.y + (size.y / 2.f);
	float my_rightX = pos.x + (size.x / 2.f);
	float my_rightY = pos.y - (size.y / 2.f);

	if (my_leftX > x || my_rightX < x || my_leftY < y || my_rightY > y)
		return false;

	return true;
}
