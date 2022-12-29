#pragma once
#include <Display/Display.h>

class OpenStartup
{
	char _className[32];
	HINSTANCE _hInstance;

	const HWND createOpenWindow(bool windowedMode, int width, int height);
public:
	OpenStartup();
	void LaunchOpenWindow(bool windowedMode);
};
