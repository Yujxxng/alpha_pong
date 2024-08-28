#include "GameStateManager.h"
#include "BaseLevel.h"
#include "..\ComponentManager\LogicComponentManager.h"
#include "..\ComponentManager\LogicComponent.h"
#include "..\ComponentManager\EngineComponentManager.h"
#include "..\ComponentManager\GraphicComponentManager.h"

GSM::GameStateManager* GSM::GameStateManager::ptr = nullptr;

GSM::GameStateManager::GameStateManager() : previousLevel(nullptr), currentLevel(nullptr)
{}

GSM::GameStateManager::~GameStateManager()
{
    if (previousLevel)
        delete previousLevel;
    if (currentLevel)
        delete currentLevel;
}

GSM::GameStateManager* GSM::GameStateManager::GetGSMPtr()
{
    if (ptr == nullptr)
    {
        ptr = new GameStateManager;
    }

    return ptr;
}

void GSM::GameStateManager::DeleteGSM()
{
    if (ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

void GSM::GameStateManager::Init()
{
    if (currentLevel)
    {
        currentLevel->Init();
    }
}

void GSM::GameStateManager::Update()
{
    if (currentLevel)
    {
        LogicComponentManager::getPtr()->Update();
        EngineComponentManager::getPtr()->Update();
        GraphicComponentManager::getPtr()->Update();

        currentLevel->Update();
    }
}

void GSM::GameStateManager::Exit()
{
    if (currentLevel)
    {
        LogicComponentManager::DeletePtr();
        EngineComponentManager::DeletePtr();
        GraphicComponentManager::DeletePtr();

        currentLevel->Exit();
    }
}

void GSM::GameStateManager::ChangeLevel(BaseLevel* newLvl)
{
    if(previousLevel)
        delete previousLevel;
    
    previousLevel = currentLevel;

    //Exit the current level
    Exit();

    //Current level is now the "next" level
    currentLevel = newLvl;

    //initialize the level
    Init();

}

bool GSM::GameStateManager::ShouldExit()
{
    return currentLevel == nullptr;
}
