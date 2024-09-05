#pragma once

#include "BaseLevel.h"

namespace Levels
{
	class Title : public GSM::BaseLevel
	{
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
