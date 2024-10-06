#pragma once

#include "BaseLevel.h"
#include "../Object/Button.h"
#include "../Object/TextInputBox.h"

namespace Levels
{
	class GameOver : public GSM::BaseLevel
	{
		//Button btn0;
		//Button btn1;
		//Button btn2;

		Button btn[3];
		TextInputBox textBox;
	public:
		virtual ~GameOver() override {};
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
