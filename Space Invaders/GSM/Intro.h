#pragma once

#include "BaseLevel.h"

#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../Resource/TextureResource.h"

namespace Levels
{
	class Intro : public GSM::BaseLevel
	{
		void Init() override;
		void Update() override;
		void Exit() override;

		void DrawTexture(AEGfxTexture* tex, float px, float py, float sx, float sy);
	};
}
