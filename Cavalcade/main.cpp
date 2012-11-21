/****************************************/
/* Cavalcade							*/
/* David Blalock 2012					*/
/****************************************/
#include "GameSystem.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	static GameSystem* Sys;
	bool result;

	Sys = new GameSystem;
	if (!Sys)
	{
		return 0;
	}

	result = Sys->Initialize();
	if (result)
	{
		Sys->Run();
	}

	Sys->Shutdown();

	return 0;
}