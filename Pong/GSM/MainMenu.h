#pragma once
#include "BaseLevel.h"
#include "../ComponentManager/GameObject.h"

namespace Levels
{
	class MainLevel : public GSM::BaseLevel
	{
		int counter = 0;

		void Init() override;
		void Update() override;
		void Exit() override;
	};
}