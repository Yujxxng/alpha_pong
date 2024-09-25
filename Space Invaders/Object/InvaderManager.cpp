#include "InvaderManager.h"
#include <random>

InvaderManager::InvaderManager()
{
}

InvaderManager::~InvaderManager()
{
}

void InvaderManager::InitInvaders()
{
	move_dir = 1;
	InvaderNum = COL * ROW;
	CurAttackNum = 0;

	invaders = new Invader*[ROW];
	for (int i = 0; i < ROW; i++)
	{
		invaders[i] = new Invader[COL];
		for (int j = 0; j < COL; j++)
		{
			std::string ID = "";
			invaders[i][j].InitInvader();

			switch (i)
			{
			case 0:
			case 1:
				//octopus
				ID = "O" + to_string(i) + to_string(j);
				invaders[i][j].SetInvader(ID, OCTOPUS, 22.f, 22.f, -(320.f / 2) + 10.f + (30.f * j), 35.f * i, 255.f, 255.f, 255.f);
				break;

			case 2:
			case 3:
				//crab
				ID = "C" + to_string(i) + to_string(j);
				invaders[i][j].SetInvader(ID, CRAB, 22.f, 22.f, -(320.f / 2) + 10.f + (30.f * j), 35.f * i, 0.f, 255.f, 255.f);
				break;

			case 4:
				//squid
				ID = "S" + to_string(i) + to_string(j);
				invaders[i][j].SetInvader(ID, SQUID, 20.f, 20.f, -(320.f / 2) + 10.f + (30.f * j), 35.f * i, 0.f, 0.f, 255.f);
				break;

			default:
				break;
			}
		}
	}

	UFO = new Invader;
	UFO->InitInvader();
	UFO->SetInvader("UFO", InvaderType::UFO, 30.f, 20.f, 0.f, (W_HEIGHT / 2) - 50.f, 255.f, 0.f, 0.f);
	UFO->SetRandomSpawn();
	UFO->SetRandomPoints();
	UFO->alive = false;
	UFO->move = false;
	UFO->Visible(false);
}

void InvaderManager::deleteInvaders()
{
	if (invaders == nullptr)
		return;

	for (int i = 0; i < ROW; i++)
		delete[] invaders[i];
	delete[] invaders;
	delete UFO;
}

Invader* InvaderManager::GetLeft()
{
	int idx = COL;
	Invader* tmp = nullptr;

	for (int j = 0; j < COL; j++)
	{
		for (int i = 0; i < ROW; i++)
		{
			if (invaders[i][j].alive && j < idx)
			{
				
				idx = j;
				tmp = &invaders[i][j];
			}
		}
	}

	return tmp;
}

Invader* InvaderManager::GetRight()
{
	int idx = -1;
	Invader* tmp = nullptr;

	for (int j = COL - 1; j >= 0; j--)
	{
		for (int i = 0; i < ROW; i++)
		{
			if (invaders[i][j].alive && j > idx)
			{

				idx = j;
				tmp = &invaders[i][j];
			}
		}
	}

	return tmp;
}

Invader* InvaderManager::GetBottom()
{
	float min = 800.f;
	Invader* p = nullptr;
	for (int i = 0; i < COL; i++)
	{
		if (Attacker[i].first)
		{
			if (min > Attacker[i].first->GetPos().y)
			{
				min = Attacker[i].first->GetPos().y;
				p = Attacker[i].first;
			}
		}
	}
	return p;
}

void InvaderManager::UpdateBottom()
{
	botNum = GetLiveAttacker();
	for (int i = ROW - 1; i >= 0; i--)
	{
		for (int j = 0; j < COL; j++)
		{
			if (i == ROW - 1)
			{
				if (invaders[i][j].alive)
					Attacker[j].first = &invaders[i][j];
				else
					Attacker[j].first = nullptr;
			}
			else
			{
				if (invaders[i][j].alive)
					Attacker[j].first = &invaders[i][j];
			}

		}
	}
}

void InvaderManager::UpdateDead()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (!invaders[i][j].alive)
				invaders[i][j].Dead();
		}
	}
}

void InvaderManager::InitAttacker()
{
	for (int i = 0; i < COL; i++)
	{
		Attacker[i].first = &invaders[0][i];
		Attacker[i].second = false;
	}
}

int InvaderManager::SetAttacker()
{
	UpdateBottom();
	int idx = 0;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, COL - 1);
	idx = dist(mt);


	if (Attacker[idx].first == nullptr || Attacker[idx].second)
	{
		for (int i = 0; i < COL; i++)
		{
			if (Attacker[i].first != nullptr && !Attacker[i].second)
				return i;
		}
	}

	return idx;
}

bool InvaderManager::IsAttacker(Invader* invader)
{
	for (int i = 0; i < COL; i++)
	{
		if (invader == Attacker[i].first)
		{
			if (Attacker[i].second)
				return true;
		}
	}
	return false;
}

int InvaderManager::GetLiveInvaders()
{
	int cnt = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (invaders[i][j].alive)
				cnt++;
		}
	}

	return cnt;
}

int InvaderManager::GetLiveAttacker()
{
	int cnt = 0;

	for (int j = 0; j < COL; j++)
	{
		if (Attacker[j].first)
			cnt++;
	}

	return cnt;
}

void InvaderManager::PrintAttacker()
{
	for (int i = 0; i < COL; i++)
		std::cout << Attacker[i].first->GetID() << " | ";
	std::cout << "\n";
}