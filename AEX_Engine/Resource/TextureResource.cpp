#include "TextureResource.h"

void TextureResource::Load(const std::string& s)
{
	data = static_cast<void*>(AEGfxTextureLoad(s.c_str()));
}

void TextureResource::Unload()
{
	if (data != nullptr)
		AEGfxTextureUnload(static_cast<AEGfxTexture*>(data));
}

AEGfxTexture* TextureResource::GetData() const
{
	return static_cast<AEGfxTexture*>(data);
}
