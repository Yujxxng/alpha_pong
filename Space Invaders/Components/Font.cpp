#include "Font.h"
#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"

#include <iostream>
Font::Font(GameObject* go) : GraphicComponent(go)
{
	ID = "Font";
}

Font::~Font()
{
	if (fontID < 0)
		ResourceManager::GetPtr()->Unload(fontName);
}

void Font::Update()
{
	if (fontID < 0)
		std::cout << "font not fount" << std::endl;

	else
	{
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		f32 width, height;
		AEGfxGetPrintSize(fontID, str.c_str(), 1.f, &width, &height);
		AEGfxPrint(fontID, str.c_str(), -width / 2 + pos.x, -height / 2 + pos.y, size, 1, 1, 1, 1);
		//AEGfxPrint(fontID, str.c_str(), pos.x, pos.y, size, color.r, color.g, color.b, 1.0f);
	}
}

void Font::SetFont(const std::string& name)
{
	fontName = name;
	fontID = ResourceManager::GetPtr()->Get<FontResource>(name)->GetData();
}

json Font::SaveToJson()
{
	return json();
}

ComponentSerializer* Font::CreateComponent(GameObject* owner)
{
	return owner->FindComponent("Font");
}
