// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "Hooking.h"
#include <iostream>
#include "Player.h"
#include <vector>




DWORD WINAPI MainThread(LPVOID param)
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);

	uintptr_t baseModule = (uintptr_t)GetModuleHandle(NULL);

	


	
	while (!GetAsyncKeyState(VK_END))
	{
		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			std::cout << "2" << std::endl;
		}
		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			std::cout << "3" << std::endl;
			HookOpenGL();
		}
		
	}
	FreeLibraryAndExitThread((HMODULE)param, 0);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, MainThread, hModule, 0, 0);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
