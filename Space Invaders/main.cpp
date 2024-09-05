// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"

#include "GSM/GameStateManager.h"
#include "GSM/MainMenu.h"
#include "ComponentManager/GameObject.h"
#include "ComponentManager/LogicComponent.h"
#include "ComponentManager/LogicComponentManager.h"
#include "ComponentManager/EngineComponentManager.h"
#include "ComponentManager/GraphicComponentManager.h"
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


	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 450, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("Space Invader");

	GSM::GameStateManager* gsm = GSM::GameStateManager::GetGSMPtr();
	// reset the system modules
	AESysReset();

	gsm->ChangeLevel(new Levels::MainLevel);

	// Game Loop
	while (gsm->ShouldExit() == false)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Your own update logic goes here
		gsm->Update();

		// Your own rendering logic goes here

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	// free the system
	AESysExit();
}