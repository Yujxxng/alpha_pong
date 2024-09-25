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
	int botNum = COL;
	int CurAttackNum = 0;

public:
	InvaderManager();
	~InvaderManager();

	void InitInvaders();
	void deleteInvaders();

	Invader* GetLeft();
	Invader* GetRight();
	Invader* GetBottom();

	void UpdateBottom();
	void UpdateDead();

	void InitAttacker();
	int SetAttacker();
	bool IsAttacker(Invader* invader);

	int GetLiveInvaders();
	int GetLiveAttacker();

	void PrintAttacker();
};