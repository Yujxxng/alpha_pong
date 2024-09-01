#include "FontResource.h"

#include <iostream>
#include "Resource.h"

void FontResource::Load(const std::string& s)
{
	s8* font = new s8(AEGfxCreateFont(s.c_str(), 72));
	data = static_cast<void*>(font);
}

void FontResource::Unload()
{
	if (data != nullptr)
		AEGfxDestroyFont(GetData());
}

s8 FontResource::GetData() const
{
	return *(static_cast<s8*>(data));
}
