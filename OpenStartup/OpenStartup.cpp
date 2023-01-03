#include "OpenStartup.h"

OpenStartup::OpenStartup()
{
	
}

const HWND OpenStartup::createOpenWindow(bool windowedMode, int width, int height)
{
	if (windowedMode)
		return CreateWindowExA(0x40000, "Open1503", "Open1503", 0x80000000,
			0, 0, width, height, 0, 0,_hInstance, 0);

	// full screen code here
	return (HWND)1;
}

void OpenStartup::LaunchOpenWindow(bool windowedMode)
{
	LoadStringA(_hInstance, 1, _className, sizeof _className);
	HWND windowA = FindWindowA(_className, 0);
	if (windowA)
	{
		if (IsIconic(windowA))
			ShowWindow(windowA, 9);
		SetForegroundWindow(windowA);
		return;
	}

	HKEY hkeyResult;
	DWORD disposition;
	RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Azukee\\Open1503", 0, 0, 0,
		0xF003F, 0, &hkeyResult, &disposition);

	if (CoInitializeEx(0, 0) < 0)
		return;

	WNDCLASSEX window = { };

	window.cbSize = sizeof WNDCLASSEX;
	window.style = 4128;
	window.lpfnWndProc = DefWindowProcA;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = _hInstance;
	window.hIcon = 0;
	//window.hCursor = LoadCursorA(hInst, 0x7A);
	//window.hbrBackground = (HBRUSH)GetStockObject(4);
	window.lpszMenuName = L"";
	window.lpszClassName = L"Open1503";
	window.hIconSm = NULL;

	if (!RegisterClassEx(&window))
		return;

	HWND hWnd = createOpenWindow(windowedMode, 1920, 1080);
	if (hWnd)
	{
		SetForegroundWindow(hWnd);
		ShowWindow(hWnd, 1);
		SetFocus(hWnd);
		
		Display* displayInstance = nullptr;

		Display::CreateDisplayInstance(false, &displayInstance);

		DrawBitmapDD7* drawBitmapInstance = displayInstance->getDrawBitmapInstance();

		drawBitmapInstance->sub_1000C9F0(hWnd, nullptr, &IID_IDirect3DHALDevice, nullptr);
		drawBitmapInstance->sub_1000D2D0(1, NULL);
		drawBitmapInstance->Present(nullptr, nullptr);
	}

}
