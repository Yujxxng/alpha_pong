#pragma once

#include "BaseLevel.h"

#include "../ComponentManager/ResourceManager.h"
#include "../Resource/FontResource.h"
#include "../Resource/TextureResource.h"
#include "../Object/TextInputBox.h"

#include "../Object/RankBoard.h"
#include "../Object/button.h"

#include "../Object/Score.h"

namespace Levels
{
	class Test : public GSM::BaseLevel
	{
		RankBoard rankBoard;
		Button btn0;
		Button btn1;

		Score* testScore;
	public:
		virtual ~Test() override {};

		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
