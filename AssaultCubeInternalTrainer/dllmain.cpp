// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "Hooking.h"
#include <iostream>
#include "Player.h"
#include <vector>

/* PlayerEntity VTable
	func 0: base + 29D70			unknown didnt get hit
	func 1: base + 10470	{ret}	something to do with shooting
	func 2: base + 649E0	{ret 4}	hits breakpoint immediatly prob used in an update func
	func 3: base + F56F4			unknown didnt get hit
	func 4: base + 29FA0			unknown didnt get hit
	func 5: base + 2A360			unknown didnt get hit, calls func 8
	func 6: base + F56E0
	func 7: base + 2FA80
	func 8: base + 2A230
	func 8: base + F5684
*/

/* _printToChat() address = 0046B060
	004E306C  25 73 3A 0C 25 64 20 25 74   -  %s:\f%d %s
	name(str)
	0 or 1
	text(str)
*/
typedef char*(__cdecl * _printToChat)(const char* sFormat, const char* characterName, int color, const char* text);
_printToChat printToChat;

DWORD WINAPI MainThread(LPVOID param)
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	Player* localPlayer = new Player();

	uintptr_t baseModule = (uintptr_t)GetModuleHandle(NULL);

	int* botArrayLength = (int*)(baseModule + 0x10F500);
	if (*botArrayLength != 0)
	{
		uintptr_t botArrayBase = (*(int*)(baseModule + 0x10F4F8)) + 0x4; //Pointers start at +0x4 from the address
		std::vector<Player> botArray;

		for (int i = 0; i < (*botArrayLength) - 1; i++)
		{
			Player tmpBot = Player(*(int*)(botArrayBase + (i * 4)));
			botArray.push_back(tmpBot);
			tmpBot.print();
		}
	}
	else
	{
		std::cout << "No bots in game" << std::endl;
	}

	printToChat = (_printToChat)(baseModule + 0x6B060);

	const char* format = "%s:\f%d %s";
	
	// 429d70
	printToChat(format, "DLL", 1, "Loaded..");
	while (!GetAsyncKeyState(VK_END))
	{
		std::cout << std::dec;
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			printToChat(format, "name", 0, "Text");
			DWORD addressToHook = (DWORD)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
			std::cout << std::hex << addressToHook << std::endl;
		}
		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			std::cout << "2" << std::endl;
			localPlayer->print();
		}
		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			std::cout << "3" << std::endl;
			HookOpenGL();
		}
		if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		{
			std::cout << "4" << std::endl;
		}
	}
	printToChat(format, "DLL", 1, "DLL Unloaded..");
	FreeLibraryAndExitThread((HMODULE)param, 0);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
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

bool Hook(void* funcToHook, void* replacementFunc, int length)
{
	// Must be greater than 5, due to the jmp instruction being 5 bytes
	if (length < 5)
		return false;
	// Change protection of the bytes, so we can write to them
	DWORD oldProtection;
	VirtualProtect(funcToHook, length, PAGE_EXECUTE_READWRITE, &oldProtection);

	memset(funcToHook, 0x90, length);

	// Offset after the jump address, so the size of the jump instruction must be taken into consideration i.e "-5"
	DWORD relativeAddress = ((DWORD)replacementFunc - (DWORD)funcToHook) - 5;

	// Set first byte to jmp
	*(BYTE*)funcToHook = 0xE9;
	// Set the jump offset, +1 so we dont overwrite the jmp byte.  ex. E9 {Offset}
	*(DWORD*)((DWORD)funcToHook) = relativeAddress + 1;

	// Change protection back to what it used to be.
	VirtualProtect(funcToHook, length, oldProtection, &oldProtection);
	return true;
}