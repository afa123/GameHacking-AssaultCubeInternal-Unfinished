#pragma once
#include <Windows.h>
#include "HelpFunctions.h"
void HookOpenGL();
__declspec() void swapBuffersTrampolineFunc();
void hWglSwapBuffers(_In_ HDC hDc);
