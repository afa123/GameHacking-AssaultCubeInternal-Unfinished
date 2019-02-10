#include "Hooking.h"
#include "OpenGL.h"

DWORD o_WglSwapBuffers = 0;
OpenGL *draw = new OpenGL();

void HookOpenGL()
{
	
}

__declspec(naked) void swapBuffersTrampolineFunc()
{
	__asm {
		
	}
}

// Draw stuff here
void hWglSwapBuffers(HDC hDc)
{
	draw->box(10, 10, 50, 50, 250, 0, 0);
}


