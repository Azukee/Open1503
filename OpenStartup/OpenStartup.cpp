#include <Windows.h>
#include <OpenDisplay.cpp>

char ClassName[32];
HINSTANCE HInstance;

LRESULT __stdcall au_re_DefWindowProcA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProcA(hWnd, Msg, wParam, lParam);
}

HWND CreateOpenWindow(bool windowedMode, int width, int height)
{
	if (windowedMode)
	{
		HWND RESULT = CreateWindowExA(0x40000, "Open1503", "Open1503", 0x80000000, 0, 0, width, height, 0, 0, HInstance, 0);
		int err = GetLastError();
		return RESULT;
	}
	// full screen code here
	return (HWND)1;
}

int LaunchOpenWindow(bool windowedMode)
{
	// Make sure Open1503 is only launched once

	LoadStringA(HInstance, 1, ClassName, sizeof ClassName);
	HWND windowA = FindWindowA(ClassName, 0);
	if (windowA)
	{
		if (IsIconic(windowA))
			ShowWindow(windowA, 9);
		SetForegroundWindow(windowA);
		return 0;
	}

	HKEY hkeyResult;
	DWORD disposition;
	RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Azukee\\Open1503", 0, 0, 0,
		0xF003F, 0, &hkeyResult, &disposition);

	if (CoInitializeEx(0, 0) < 0)
		return 0;

	WNDCLASSEX window = { };

	window.cbSize = sizeof WNDCLASSEX;
	window.style = 4128;
	window.lpfnWndProc = au_re_DefWindowProcA;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = HInstance;
	window.hIcon = 0;
	//window.hCursor = LoadCursorA(hInst, 0x7A);
	//window.hbrBackground = (HBRUSH)GetStockObject(4);
	window.lpszMenuName = L"";
	window.lpszClassName = L"Open1503";
	window.hIconSm = NULL;

	if (!RegisterClassEx(&window))
		return 0;

	HWND result = CreateOpenWindow(windowedMode, 800, 600);
	if (result)
	{
		SetForegroundWindow(result);
		ShowWindow(result, 1);
		SetFocus(result);

		Display* displayInstance = nullptr;
		OpenDisplay::CreateDisplayInstance(false, &displayInstance);


	}

	return 0;
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	HInstance = hInst;
	auto mutex = CreateMutexA(0, 0, "OPEN1503_EXE_Mutex");
	char commandLine[260] = {};
	
	HKEY v19 = 0;

	char destination[48] = {};
	char ip[12] = { "127.0.0.1" };
	char Str2[8];

	strcpy_s(Str2, "connect");
	strcpy_s(commandLine, cmdline);

	
	LaunchOpenWindow(true);
	// 
}
