#pragma once

#include "BaseLevel.h"

namespace Levels
{
	class GameOver : public GSM::BaseLevel
	{
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
