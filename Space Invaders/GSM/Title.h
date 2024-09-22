#pragma once

#include "BaseLevel.h"

#include "AEEngine.h"

namespace Levels
{
	class Title : public GSM::BaseLevel
	{
		void Init() override;
		void Update() override;
		void Exit() override;

		void DrawTexture(AEGfxTexture* tex, float px, float py, float sx, float sy, float a);
	};
}
