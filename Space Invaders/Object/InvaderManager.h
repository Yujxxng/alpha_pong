#pragma once
#include "Invader.h"
#include "BulletManager.h"

class InvaderManager
{
public:
	Invader** invaders;
	Invader* UFO;
	std::pair<Invader*, bool> Attacker[COL];
	
	int move_dir = 1;
	int InvaderNum = COL * ROW;
	int AttackerNum = 2;

	int Stage = 0;
public:
	InvaderManager();
	~InvaderManager();

	void InitInvaders();
	void deleteInvaders();
	void ResetInvaders();
	void DeadAllInvaders();

	Invader* GetLeft();
	Invader* GetRight();
	Invader* GetBottom();

	int GetLiveInvaders();
	
	void UpdateBottom();
	void UpdateDead();

	void InitAttacker();
	int SetAttacker();
};