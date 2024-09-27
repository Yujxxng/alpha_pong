#pragma once

#include "BaseLevel.h"
#include "../Object/Button.h"
namespace Levels
{
	class GoalLevel : public GSM::BaseLevel
	{
		Button btn0;
		Button btn1;

	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
