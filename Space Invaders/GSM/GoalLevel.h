#pragma once

#include "BaseLevel.h"
#include "../Object/Button.h"
#include "../Object/TextInputBox.h"

namespace Levels
{
	class GoalLevel : public GSM::BaseLevel
	{
		Button goal_btn[3];
		TextInputBox goal_textBox;

	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
