// ---------------------------------------------------------------------------
// includes
#include <cwchar>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"

#include "GSM/GameStateManager.h"
#include "GSM/MainMenu.h"
#include "GSM/Title.h"
#include "GSM/Intro.h"
#include "GSM/GoalLevel.h"
#include "GSM/GameOver.h"

#include "GSM/Test.h"

#include "ComponentManager/GameObject.h"
#include "ComponentManager/LogicComponent.h"
#include "ComponentManager/LogicComponentManager.h"
#include "ComponentManager/EngineComponentManager.h"
#include "ComponentManager/GraphicComponentManager.h"
#include "ComponentManager/ResourceManager.h"
// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialization of your own variables go here
	s32 show_console = 0;
	wchar_t str[] = L"console";
	if (wcscmp(lpCmdLine, str)==0)
	{
		show_console = 1;
	}

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 450, 600, show_console, 60, true, NULL);
	
	// Changing the window title
	AESysSetWindowTitle("Digipen Invaders");

	GSM::GameStateManager* gsm = GSM::GameStateManager::GetGSMPtr();
	// reset the system modules
	AESysReset();
	
	gsm->ChangeLevel(new Levels::Title);

	// Game Loop
	while (gsm->gGameRunning)
	{
		// gsm current state != next state => state changed
			// then, current state exit
			//       next state init
		    //       delete current state
		    //       current state = next state

		// Informing the system about the loop's start
		AESysFrameStart();

		// Your own update logic goes here
		gsm->Update();

		// Your own rendering logic goes here

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gsm->gGameRunning = 0;
	}

	Score* s = Score::getPtr();
	s->DeletePtr();
	ResourceManager* rm = ResourceManager::GetPtr();
	rm->DeletePtr();

	gsm->Exit();
	gsm->DeleteGSM();

	// free the system
	AESysExit();
}
