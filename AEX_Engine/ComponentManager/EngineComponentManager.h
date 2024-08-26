#pragma once
#include "GameObject.h"
#include "EngineComponent.h"
#include "list"


//singleton
class EngineComponentManager
{
	EngineComponentManager() = default;
	~EngineComponentManager() = default;
	
	EngineComponentManager(const EngineComponentManager&) = delete;
	const EngineComponentManager& operator=(const EngineComponentManager& other) = delete;

	static EngineComponentManager* engine_ptr;
	list<EngineComponent*> engines;

public:
	static EngineComponentManager* getPtr();
	static void DeletePtr();

	void AddEngine(EngineComponent* lc);
	void DeleteEngine(EngineComponent* c);
	void Update();
};