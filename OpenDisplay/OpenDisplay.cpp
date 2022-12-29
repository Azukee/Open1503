// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "Display/Display.h"

static HMODULE dword_1004E318;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        dword_1004E318 = hModule;

    return TRUE;
}

