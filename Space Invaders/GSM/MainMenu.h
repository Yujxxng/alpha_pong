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

		Invader* Octopus0[COL];
		Invader* Octopus1[COL];
		Invader* Crab0[COL];
		Invader* Crab1[COL];
		Invader* Squid[COL];
		Invader* UFO;

		//Invader* Attacker[11];
		std::pair<Invader*, bool> Attacker[COL];
		Wall* wLeft, * wRight;
		Wall* wTop, * wBot;
		
		void Init() override;
		void Update() override;
		void Exit() override;

	public:
		Invader* GetLeft();
		Invader* GetRight();

		void UpdateBottom();
		void InitAttacker();
		void SetAttacker(int n);

		int GetLiveAttacker();
		int GetLiveInvaders();
		void PrintAttacker();
	};
}