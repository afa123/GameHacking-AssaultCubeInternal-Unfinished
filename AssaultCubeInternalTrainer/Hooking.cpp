#include "Hooking.h"
#include "OpenGL.h"

DWORD oWglSwapBuffers = 0;
OpenGL *draw = new OpenGL();
void HookOpenGL()
{
	DWORD addressToHook = (DWORD)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
	oWglSwapBuffers = HelpFunctions::JumpHook(addressToHook, (DWORD)swapBuffersTrampolineFunc, 5);
}

__declspec(naked) void swapBuffersTrampolineFunc()
{
	__asm {
		PUSHFD
		PUSHAD
		CALL hWglSwapBuffers
		POPAD
		POPFD
		push ebp
		mov ebp, esp
		JMP[oWglSwapBuffers]
	}
}

// Draw stuff here
void hWglSwapBuffers(HDC hDc)
{
	draw->box(10, 10, 50, 50, 250, 0, 0);
}


