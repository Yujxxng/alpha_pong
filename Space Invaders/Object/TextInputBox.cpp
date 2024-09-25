#include "TextInputBox.h"

#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../Resource/TextureResource.h"

#include <iostream>
#include <fstream>

TextInputBox::TextInputBox()
{
	font = ResourceManager::GetPtr()->Get<FontResource>("Assets/space_invaders.ttf")->GetData();

	f32 width = 0, height = 0;
	AEGfxGetPrintSize(font, "ABCDEFGHIJKLMN", 1.f, &width, &height);

	boxSize.x = AEGfxGetWindowWidth() * width / 2.f;
	boxSize.y = AEGfxGetWindowHeight() * height / 2.f;

	barSize.x = 2.5f;
	barSize.y = boxSize.y;

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

	char offset = 0;
	for (u8 curr = AEVK_A; curr <= AEVK_Z; curr++)
	{
		allowedKeys.push_back(std::make_pair(curr, 'A' + offset));
		offset++;
	}
	allowedKeys.push_back(std::make_pair(AEVK_SPACE, ' '));
	//allowedKeys.push_back(std::make_pair(AEVK_A, 'A'));
}

TextInputBox::~TextInputBox()
{
	AEGfxMeshFree(mesh);
}

void TextInputBox::Update(float dt)
{
	UpdateText();

	DrawTextInputBox();
	
	if(text.empty())
		DrawBar(dt);

	DrawUserText();
}

void TextInputBox::DrawTextInputBox()
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetColorToMultiply(boxColor.r, boxColor.g, boxColor.b, 1);
	AEGfxSetColorToAdd(0, 0, 0, 0);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, boxSize.x + boxMargin.x, boxSize.y + boxMargin.y);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, boxPos.x, boxPos.y);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	AEGfxSetTransform(transform.m);

	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void TextInputBox::DrawBar(float dt)
{
	blinkDt += dt;
	if (blinkDt >= blinkSpeed)
	{
		if (barVisible)
		{
			barVisible = false;
		}
		else
		{
			barVisible = true;
		}
		blinkDt = 0.f;
	}

	if (barVisible)
	{
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetColorToMultiply(barColor.r / 255.f, barColor.g / 255.f, barColor.b / 255.f, 1.f);
		AEGfxSetColorToAdd(0, 0, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1);

		AEMtx33 scale = { 0 };
		AEMtx33Scale(&scale, barSize.x, barSize.y);

		AEMtx33 rotate = { 0 };
		AEMtx33Rot(&rotate, 0);

		AEMtx33 translate = { 0 };
		AEMtx33Trans(&translate, barPos.x, barPos.y);

		AEMtx33 transform = { 0 };
		AEMtx33Concat(&transform, &rotate, &scale);
		AEMtx33Concat(&transform, &translate, &transform);

		AEGfxSetTransform(transform.m);

		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	}
}

void TextInputBox::DrawUserText()
{
	f32 width, height;
	AEGfxGetPrintSize(font, text.c_str(), 1.f, &width, &height);

	float x = boxPos.x * 2.f / AEGfxGetWindowWidth();
	float y = boxPos.y * 2.f / AEGfxGetWindowHeight();

	AEGfxPrint(font, text.c_str(), x - (width / 2), y - (height / 2), 1.f, 0, 0, 1, 1);
}

void TextInputBox::UpdateText()
{
	if (inputEnabled)
	{
		if (text.size() < MaxTextLen)
		{
			for (const auto& key : allowedKeys)
			{
				if (AEInputCheckTriggered(key.first))
					text.push_back(key.second);
			}
		}

		if (!text.empty())
		{
			if (AEInputCheckTriggered(AEVK_BACK))
				text.pop_back();
		}
	}

	if (AEInputCheckTriggered(AEVK_RETURN))
	{
		inputEnabled = !inputEnabled;
		SaveToJson();
	}
}

void TextInputBox::SaveToJson()
{
	std::ofstream jf("data.json");

	if (!jf.is_open())
	{
		std::cout << "FILE NOT FOUND" << std::endl;
		return;
	}
	using json = nlohmann::json;
	json data;
	data["text"] = text;
	
	std::string tmp = data.dump(-1);
	jf.write(tmp.c_str(), tmp.size());

	jf.close();
}

void TextInputBox::LoadFromJson()
{
	std::ifstream jf("data.json");

	if (!jf.is_open())
	{
		std::cout << "FILE NOT FOUND" << std::endl;
		return;
	}
	using json = nlohmann::json;
	json data;
	jf >> data;
	text = data.at("text").get<std::string>();

	jf.close();
}
