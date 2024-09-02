#pragma once
#include <string>

struct Event
{
	Event();
	virtual ~Event();
public:
	std::string name;

	const std::string getID() const { return name; }
};

class Entity
{
public:
	virtual void OnEvent(Event* ev) = 0;
};

class LocalEvent : public Event //custom event
{
	Entity* Owner;
};

#include <queue>
#include <list>
#include <map>

class EventManager
{
	EventManager(const EventManager& other) = delete;
	const EventManager& operator= (const EventManager& other) = delete;

	static EventManager* event_ptr;

	//A container to have which entities are registered to which events
	//map of (events, container of entities)
	std::queue<Event*> allEvents;
	std::map<std::string, std::list<Entity*>> map_Entites;

protected:
	EventManager() = default;
	~EventManager() = default;

public:
	static EventManager* GetPtr();
	static void DeletePtr();

	//interface:
	//Add an event (event*) this are pointers to dynamic memory, called as the following : AddEvent(new Event);
	void AddEvent(Event* e);

	// templated fn:
	//		Register entities to a certain event TYPE
	void RegisterEnt(std::string event, Entity* ent);
	//		Unregister entities to a certain event TYPE
	void UnregisterEnt(std::string event, Entity* ent);
	void DispatchAll();

	//delete undispatched events if any on destructor
	//void DeleteUndispatched();
};
