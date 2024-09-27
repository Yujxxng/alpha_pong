#pragma once

#include "BaseLevel.h"

#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../Resource/TextureResource.h"
#include "../Object/TextInputBox.h"

#include "../Object/RankBoard.h"

namespace Levels
{
	class Test : public GSM::BaseLevel
	{
		RankBoard rankBoard;
	public:
		virtual ~Test() override {};

		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
