// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "Display/Display.h"

static HMODULE dword_1004E318;

class __declspec(dllexport) OpenDisplay
{
public:
    static void __cdecl CreateDisplayInstance(bool unknown, Display** display)
    {
        // If the unknown bool is set to true, DisplayEdit is returned instead of display

        // TODO: write unknown == true code here

        const auto displayInstance = new Display();
        displayInstance->createDrawBitmapDD7();
        *display = displayInstance;
    }
};

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        dword_1004E318 = hModule;

    return TRUE;
}

