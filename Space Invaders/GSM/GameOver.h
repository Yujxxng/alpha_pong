#pragma once

#include "BaseLevel.h"
#include "../Object/Button.h"
#include "../Object/TextInputBox.h"

extern bool save;
extern int activeKey;
namespace Levels
{
	class GameOver : public GSM::BaseLevel
	{
		Button btn[3];
		TextInputBox textBox;
	public:
		virtual ~GameOver() override {};
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
