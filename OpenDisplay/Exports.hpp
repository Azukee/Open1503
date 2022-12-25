#pragma once
#include <Windows.h>
#include "tDisplay.h"

static int CreateDisplayInstance(int a1, int* instance)
{
	*instance = NULL;

    void* v2; // eax
    int v3; // esi
    void* v4; // eax
    int result; // eax

    if (a1)
    {
        if (a1 != 1)
            return 0x80004005;
        v4 = operator new(0x18u);
        v3 = (int)v4;
        if (v4)
        {
            //sub_10026580(v4);
            //*(_DWORD*)v3 = &tDisplayEdit::`vftable';
        }
        else
        {
            v3 = 0;
        }
    }
    else
    {
        v2 = operator new(0x18u);
        if (v2)
        {
            v3 = /*sub_10026580(v2)*/ 0;

            DWORD* result = (DWORD*)v3;
            *result = reinterpret_cast<DWORD*>(&tDisplay::vfC);
        }
        else
            v3 = 0;
    }
    if (!v3)
        return 0x80004005;
    result = (*(int(__thiscall**)(int))(*(DWORD*)v3 + 140))(v3);
    if (result < 0)
        return result;
    *instance = v3;
    return 0;



}