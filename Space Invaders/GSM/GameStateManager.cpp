#include "GameStateManager.h"
#include "BaseLevel.h"
#include "..\ComponentManager\LogicComponentManager.h"
#include "..\ComponentManager\LogicComponent.h"
#include "..\ComponentManager\EngineComponentManager.h"
#include "..\ComponentManager\GraphicComponentManager.h"
#include "..\ComponentManager\EventManager.h"
#include "..\ComponentManager\ResourceManager.h"
#include "../Object/Score.h"
#include <iostream>

GSM::GameStateManager* GSM::GameStateManager::ptr = nullptr;

GSM::GameStateManager::GameStateManager() : currentLevel(nullptr), nextLevel(nullptr)
{

    for (u8 curr = AEVK_LBUTTON; curr <= AEVK_MBUTTON; curr++)
        anyKeys.push_back(curr);
 
    for (u8 curr = AEVK_BACK; curr <= AEVK_CAPSLOCK; curr++)
        anyKeys.push_back(curr);

    for (u8 curr = AEVK_SPACE; curr <= AEVK_DELETE; curr++)
        anyKeys.push_back(curr);

    for (u8 curr = AEVK_0; curr <= AEVK_Z; curr++)
    {
        if (curr >= 0x3A && curr <= 0x40)
            continue;
        anyKeys.push_back(curr);
    }
    
    for (u8 curr = AEVK_NUMPAD0; curr <= AEVK_NUMPAD9; curr++)
        anyKeys.push_back(curr);

    for (u8 curr = AEVK_NUM_MULTIPLY; curr <= AEVK_NUMLOCK; curr++)
        anyKeys.push_back(curr);

    for (u8 curr = AEVK_F1; curr <= AEVK_F12; curr++)
        anyKeys.push_back(curr);

    for (u8 curr = AEVK_SEMICOLON; curr <= AEVK_QUOTE; curr++)
        anyKeys.push_back(curr);

    for (u8 curr = AEVK_EQUAL; curr <= AEVK_COMMA; curr++)
        anyKeys.push_back(curr);
}

GSM::GameStateManager::~GameStateManager()
{
    if (currentLevel)
    {
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
    if (nextLevel)
    {
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
        if(currentLevel == nextLevel)
            nextLevel = nullptr;

        currentLevel->Exit();

        delete currentLevel;
        currentLevel = nullptr;
    }
    LogicComponentManager::DeletePtr();
    EngineComponentManager::DeletePtr();
    GraphicComponentManager::DeletePtr();
    
    //EventManager::DeletePtr();
}

void GSM::GameStateManager::ChangeLevel(BaseLevel* newLvl)
{
    nextLevel = newLvl;
}

bool GSM::GameStateManager::ShouldExit()
{
    return currentLevel == nullptr;
}
