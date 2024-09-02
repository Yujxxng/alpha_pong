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

		Wall* wLeft, * wRight;
		
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}