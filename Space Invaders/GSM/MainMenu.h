#pragma once
#include "BaseLevel.h"
#include "../ComponentManager/GameObject.h"

#include "../Object/Player.h"
#include "../Object/Invader.h"
#include "../Object/Wall.h"
namespace Levels
{
	class MainLevel : public GSM::BaseLevel
	{
		int counter = 0;

		Player* player;

		Invader* Octopus0[11];
		Invader* Octopus1[11];
		Invader* Crab0[11];
		Invader* Crab1[11];
		Invader* Squid[11];
		Invader* UFO;

		Bullet* missile[5];

		Wall* wLeft, * wRight;
		Wall* wTop;// , * wBot;
		
		void Init() override;
		void Update() override;
		void Exit() override;

	public:
		Invader* GetLeft();
		Invader* GetRight();
		
		void SetAttaker();
		void SetInvaderBullet();
	};
}