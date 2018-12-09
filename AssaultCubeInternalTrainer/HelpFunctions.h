#pragma once
#include <Windows.h>

namespace HelpFunctions
{
	template<typename T> T Read(DWORD address);
	template<typename T> void Write(DWORD address, T value);
	template<typename T> DWORD Protect(DWORD address, DWORD prot);
	DWORD JumpHook(DWORD hookAt, DWORD newFunc, int size);

	bool Hook(void* funcToHook, void* replacementFunc, int length);
	DWORD TrampolineHook(DWORD funcToHook, DWORD replacementFunc, int length);
}
