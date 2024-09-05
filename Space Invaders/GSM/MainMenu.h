#pragma once
#include "BaseLevel.h"
#include "../ComponentManager/GameObject.h"

#include "../Object/Player.h"
#include "../Object/Invader.h"
#include "../Object/Wall.h"
#include "../Object/Score.h"


namespace Levels
{
	class MainLevel : public GSM::BaseLevel
	{
		Score* score;

		Player* player;

		Invader* Octopus0[COL];
		Invader* Octopus1[COL];
		Invader* Crab0[COL];
		Invader* Crab1[COL];
		Invader* Squid[COL];
		Invader* UFO;

		std::pair<Invader*, bool> Attacker[COL];
		Wall* wLeft, * wRight;
		Wall* wTop, * wBot;
		
		void Init() override;
		void Update() override;
		void Exit() override;

	public:
		void Stop();
		Invader* GetLeft();
		Invader* GetRight();
		Invader* GetBottom();

		void UpdateBottom();
		void UpdateDead();
		void InitAttacker();
		void SetAttacker(int n);
		bool IsAttacker(Invader* invader);

		int GetLiveAttacker();
		int GetLiveInvaders();
		void PrintAttacker();
	};
}