#include "HelpFunctions.h"

template<typename T>
T HelpFunctions::Read(DWORD address)
{
	return *((T*)address);
}

template<typename T>
void HelpFunctions::Write(DWORD address, T value)
{
	*((T*)address) = value;
}

template<typename T>
DWORD HelpFunctions::Protect(DWORD address, DWORD prot)
{
	DWORD oldProt;
	VirtualProtect((LPVOID)address, sizeof(T), prot, &oldProt);
	return oldProt;
}

DWORD HelpFunctions::JumpHook(DWORD hookAt, DWORD newFunc, int size)
{
	DWORD newOffset = newFunc - hookAt - 5; // -5 cuz its relative to the next instruction
	auto oldProtection = HelpFunctions::Protect<DWORD[3]>(hookAt + 1, PAGE_EXECUTE_READWRITE);
	HelpFunctions::Write<BYTE>(hookAt, 0xE9); //JMP
	HelpFunctions::Write<DWORD>(hookAt + 1, newOffset);
	for (unsigned int i = 5; i < size; i++) //NOP extra bytes so it doesnt corrupt any instructions
		HelpFunctions::Write<BYTE>(hookAt + i, 0x90);
	HelpFunctions::Protect<DWORD[3]>(hookAt + 1, oldProtection);
	return hookAt + 5;
}

bool HelpFunctions::Hook(void * funcToHook, void * replacementFunc, int length)
{
	// Must be greater or equal to 5, due to the jmp instruction being 5 bytes
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

DWORD HelpFunctions::TrampolineHook(DWORD funcToHook, DWORD replacementFunc, int length)
{
	// Must be greater or equal to 5, due to the jmp instruction being 5 bytes
	if (length < 5)
		return 0;
	// Change protection of the bytes, so we can write to them
	DWORD oldProtection;
	VirtualProtect((LPVOID)funcToHook, length, PAGE_EXECUTE_READWRITE, &oldProtection);
	
	memset((LPVOID)funcToHook, 0x90, length);

	// Offset after the jump address, so the size of the jump instruction must be taken into consideration i.e "-5"
	DWORD relativeAddress = ((DWORD)replacementFunc - (DWORD)funcToHook) - 5;

	// Set first byte to jmp
	*(BYTE*)funcToHook = 0xE9;
	// Set the jump offset, +1 so we dont overwrite the jmp byte.  ex. E9 {Offset}
	*(DWORD*)((DWORD)funcToHook) = relativeAddress + 1;

	// Change protection back to what it used to be.
	VirtualProtect((LPVOID)funcToHook, length, oldProtection, &oldProtection);
	return (DWORD)funcToHook + length;
}
