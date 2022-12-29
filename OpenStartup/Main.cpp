#include <Windows.h>

#include "OpenStartup.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	/*HInstance = hInst;
	auto mutex = CreateMutexA(0, 0, "OPEN1503_EXE_Mutex");
	char commandLine[260] = {};
	
	HKEY v19 = 0;

	char destination[48] = {};
	char ip[12] = { "127.0.0.1" };
	char Str2[8];

	strcpy_s(Str2, "connect");
	strcpy_s(commandLine, cmdline);*/

	OpenStartup os = OpenStartup();
	os.LaunchOpenWindow(true);
	
	// 
}
