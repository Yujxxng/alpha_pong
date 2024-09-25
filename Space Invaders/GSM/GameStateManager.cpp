#include "GameStateManager.h"
#include "BaseLevel.h"
#include "..\ComponentManager\LogicComponentManager.h"
#include "..\ComponentManager\LogicComponent.h"
#include "..\ComponentManager\EngineComponentManager.h"
#include "..\ComponentManager\GraphicComponentManager.h"
#include "..\ComponentManager\EventManager.h"
#include "..\ComponentManager\ResourceManager.h"
#include <iostream>

GSM::GameStateManager* GSM::GameStateManager::ptr = nullptr;

GSM::GameStateManager::GameStateManager() : currentLevel(nullptr), nextLevel(nullptr)
{
    std::cout << __FUNCTION__ << std::endl;
}

GSM::GameStateManager::~GameStateManager()
{
    if (currentLevel)
    {
        std::cout << __FUNCTION__ << std::endl;
        if (currentLevel == nextLevel)
            nextLevel = nullptr;
        delete currentLevel;
    }

    if (nextLevel)
        delete nextLevel;
}

GSM::GameStateManager* GSM::GameStateManager::GetGSMPtr()
{
    if (ptr == nullptr)
    {
        std::cout << __FUNCTION__ << std::endl;
        ptr = new GameStateManager;
    }

    return ptr;
}

void GSM::GameStateManager::DeleteGSM()
{
    if (ptr)
    {
        std::cout << __FUNCTION__ << std::endl;
        delete ptr;
        ptr = nullptr;
    }
}

void GSM::GameStateManager::Init()
{
    if (nextLevel)
    {
        std::cout << __FUNCTION__ << std::endl;
        nextLevel->Init();
    }
}

void GSM::GameStateManager::Update()
{
    if (currentLevel != nextLevel)
    {
        Exit(); //currentLevel
        Init(); //nextLevel

        currentLevel = nextLevel;

        std::cout << __FUNCTION__ << std::endl;
    }

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
        std::cout << __FUNCTION__ << std::endl;
        if(currentLevel == nextLevel)
            nextLevel = nullptr;

        LogicComponentManager::DeletePtr();
        EngineComponentManager::DeletePtr();
        GraphicComponentManager::DeletePtr();
        //EventManager::DeletePtr();
        //ResourceManager::DeletePtr();

        currentLevel->Exit();

        delete currentLevel;
        currentLevel = nullptr;
    }
}

void GSM::GameStateManager::ChangeLevel(BaseLevel* newLvl)
{
#if 0
    if(previousLevel)
        delete previousLevel;
    
    previousLevel = currentLevel;

    //Exit the current level
    Exit();

    //Current level is now the "next" level
    currentLevel = newLvl;

    //initialize the level
    Init();
#elif 1
    nextLevel = newLvl;
#endif
}

bool GSM::GameStateManager::ShouldExit()
{
    return currentLevel == nullptr;
}
