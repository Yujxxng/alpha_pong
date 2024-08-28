#include "EventManager.h"
#include <list>

EventManager* EventManager::event_ptr = nullptr;

EventManager* EventManager::GetPtr()
{
	if (event_ptr == nullptr)
	{
		event_ptr = new EventManager;
		return event_ptr;
	}
	else
		return nullptr;
}

void EventManager::DeletePtr()
{
	if (event_ptr != nullptr)
	{
		delete event_ptr;
		event_ptr = nullptr;
	}
}

void EventManager::AddEvent(Event* e)
{
	allEvents.push(e);
}

void EventManager::RegisterEnt(std::string event, Entity* ent)
{
	if (map_Entites.find(event) != map_Entites.end())
		map_Entites[event].push_back(ent);
	else
	{
		std::list<Entity*> tmp;
		tmp.push_back(ent);

		map_Entites.insert({ event, tmp });
	}
}

void EventManager::UnregisterEnt(std::string event, Entity* ent)
{
	auto& tmp = map_Entites[event];
	for (auto it = tmp.begin(); it != tmp.end(); ++it)
	{
		if (*it == ent)
		{
			tmp.erase(it);
			return;
		}
	}
	/*
	if (map_Entites.find(event) != map_Entites.end())
	{
		map_Entites[event].remove(ent);
	}
	*/
}

void EventManager::DispatchAll()
{
	if (allEvents.empty())
		return;

	while (!allEvents.empty())
	{
		Event* e = allEvents.front();

		if (map_Entites.find(e->getID()) != map_Entites.end())
		{
			auto it = map_Entites.find(e->getID());
			for (auto i = it->second.begin(); i != it->second.end(); i++)
			{
				(*i)->OnEvent(e);
			}
		}

		allEvents.pop();
	}
}

//void EventManager::DeleteUndispatched()