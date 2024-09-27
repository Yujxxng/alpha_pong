#pragma once
#include "BaseLevel.h"
#include "../ComponentManager/GameObject.h"

#include "../Object/Player.h"
#include "../Object/Invader.h"
#include "../Object/Wall.h"
#include "../Object/Score.h"
#include "../Object/InvaderManager.h"
#include "../Object/BulletManager.h"

extern int TotalScore;
extern int HighScore;

namespace Levels
{
	class MainLevel : public GSM::BaseLevel
	{
		BulletManager bulletMgt;
		InvaderManager invaderMgt;
		
		Score* score;
		Player* player;

		Wall* wLeft, * wRight;
		Wall* wTop, * wBot;

	public:
		~MainLevel() override;
		void Init() override;
		void Update() override;
		void Exit() override;

		void ReLoad();
		void Stop(float t);
	};
}