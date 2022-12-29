#include "DrawBitmapDD7.h"

#include <exception>

DrawBitmapDD7::DrawBitmapDD7()
{
	WindowScreenPos = new RECT();
	WindowRect = RECT();

	ScreenPoint = new POINT();


	field_54 = 1;
	
	windowWidth_CHECK = 800;
	windowHeight_CHECK = 600;
}

void DrawBitmapDD7::sub_1000C9F0(HWND hWnd, GUID* id, const GUID* lpGuid, RECT* a5)
{
	DWORD ddsclFlags;
	DDSURFACEDESC2 ddSurfaceDesc2 = { };

	windowHandle = hWnd;

	if (a5)
	{
		WindowScreenPos = a5;
		WindowRect = *a5;
		ddsclFlags = DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT | DDSCL_FULLSCREEN;
	}
	else
	{
		GetClientRect(hWnd, WindowScreenPos);
		GetClientRect(hWnd, &WindowRect);

		ClientToScreen(hWnd, reinterpret_cast<LPPOINT>(&WindowScreenPos));
		ClientToScreen(hWnd, ScreenPoint);

		if (WindowRect.right == WindowRect.left || WindowRect.bottom == WindowRect.top)
			return /*0*/;
		ddsclFlags = DDSCL_NORMAL;
	}

	using fnDirectDrawCreateEx = HRESULT(WINAPI* )(const GUID* lpGuid, LPVOID* lplpDD, const IID* iid, IUnknown* pUnkOuter);

	HMODULE ddrawModule = LoadLibraryA("Ddraw.dll");
	const auto DirectDrawCreateEx = reinterpret_cast<fnDirectDrawCreateEx>(
		GetProcAddress(ddrawModule, "DirectDrawCreateEx"));
	
	DirectDrawCreateEx(id, reinterpret_cast<LPVOID*>(&iDirectDraw7Interface), &IID_IDirectDraw7, 0);

	if (FAILED(iDirectDraw7Interface->SetCooperativeLevel(hWnd, ddsclFlags)))
		throw std::exception("error: failed to set cooperative level");

	if ((ddsclFlags & DDSCL_FULLSCREEN) != 0) // if not fullscreen
	{
		// TODO: implement
	}

	ZeroMemory(&ddSurfaceDesc2, sizeof ddSurfaceDesc2);
	ddSurfaceDesc2.dwSize = sizeof ddSurfaceDesc2;
	if (FAILED(iDirectDraw7Interface->GetDisplayMode(&ddSurfaceDesc2)))
		throw std::exception("error: failed to get display mode");

	if (ddSurfaceDesc2.ddpfPixelFormat.dwRGBBitCount < 16)
		return; // TODO: show message box (Please select 16bpp Mode !)

	ZeroMemory(&ddSurfaceDesc2, sizeof ddSurfaceDesc2);
	ddSurfaceDesc2.dwSize = sizeof ddSurfaceDesc2;
	ddSurfaceDesc2.dwFlags = DDSD_CAPS;
	ddSurfaceDesc2.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	
	if (FAILED(iDirectDraw7Interface->CreateSurface(&ddSurfaceDesc2, &iDirectDrawSurface7_Primary, nullptr)))
		throw std::exception("error: failed to create primary ddraw surface");

	ZeroMemory(&ddSurfaceDesc2, sizeof ddSurfaceDesc2);
	ddSurfaceDesc2.dwSize = sizeof ddSurfaceDesc2;
	ddSurfaceDesc2.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	// TODO: these flags indicate that this surface is NOT the backbuffer, reverse this some more!
	ddSurfaceDesc2.ddsCaps.dwCaps = DDSCAPS_3DDEVICE | DDSCAPS_OFFSCREENPLAIN;

	// TODO: this part is incorrect, reverse!
	ddSurfaceDesc2.dwWidth = 1920;
	ddSurfaceDesc2.dwHeight = 1080;

	if (FAILED(iDirectDraw7Interface->CreateSurface(&ddSurfaceDesc2, &iDirectDrawSurface7_BackBuffer, nullptr)))
		throw std::exception("error: failed to create backbuffer");

	ZeroMemory(&ddSurfaceDesc2, sizeof ddSurfaceDesc2);
	ddSurfaceDesc2.dwSize = sizeof ddSurfaceDesc2;

	if (FAILED(iDirectDrawSurface7_BackBuffer->GetSurfaceDesc(&ddSurfaceDesc2)))
		throw std::exception("error: failed to get surface descriptor");

	// TODO: this should be it's own function
	struct random // TODO: figure out what this is
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		int unknown;
	};

	auto a1 = new random();
	auto a2 = ddSurfaceDesc2.ddpfPixelFormat.dwRBitMask;
	auto a3 = ddSurfaceDesc2.ddpfPixelFormat.dwGBitMask;
	auto a4 = ddSurfaceDesc2.ddpfPixelFormat.dwBBitMask;

	/*a2 F8000 dwRBitMask
		a3 0x7E0 dwGBitMask
		a4 0x1F dwBBitMask*/

	// TODO: make this pretty
	for (a1->r = 0; a2; ++a1->r)
		a2 &= a2 - 1;
	for (a1->g = 0; a3; ++a1->g)
		a3 &= a3 - 1;
	for (a1->b = 0; a4; ++a1->b)
		a4 &= a4 - 1;
	auto v7 = a1->r + a1->g + a1->b;
	v7 = (v7 & 0xff) | (v7 > 16);
	--v7;
	v7 = (v7 & 0xff) | (v7 & 0xF0);
	auto result = v7 + 0x20;
	a1->unknown = result;

	surfacePitch = ddSurfaceDesc2.lPitch;
}