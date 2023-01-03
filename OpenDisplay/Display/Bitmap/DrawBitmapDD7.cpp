#include "DrawBitmapDD7.h"

#include "../../Utilities/ColorUtilities.h"
#include "../../Time/QueryPerformance.h"
#include <exception>

DrawBitmapDD7::DrawBitmapDD7()
{
	WindowScreenPos = RECT();
	WindowRect = RECT();

	ScreenPoint = new POINT();


	_canPresent = true;

	_windowWidth = 800;
	_windowHeight = 600;
}

void DrawBitmapDD7::sub_1000C9F0(HWND hWnd, GUID* id, const GUID* lpGuid, RECT* a5)
{
	DWORD ddsclFlags;
	DDSURFACEDESC2 ddSurfaceDesc2 = { };

	windowHandle = hWnd;

	if (a5)
	{
		WindowScreenPos = *a5;
		WindowRect = *a5;
		ddsclFlags = DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT | DDSCL_FULLSCREEN;
	}
	else
	{
		GetClientRect(hWnd, &WindowScreenPos);
		GetClientRect(hWnd, &WindowRect);

		ClientToScreen(hWnd, reinterpret_cast<LPPOINT>(&WindowScreenPos));
		ClientToScreen(hWnd, ScreenPoint);

		if (WindowRect.right == WindowRect.left || WindowRect.bottom == WindowRect.top)
			return /*0*/;
		ddsclFlags = DDSCL_NORMAL;
	}

	using fnDirectDrawCreateEx = HRESULT(WINAPI*)(const GUID* lpGuid, LPVOID* lplpDD, const IID* iid, IUnknown* pUnkOuter);

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
	
	ddSurfaceDesc2.dwWidth = WindowScreenPos.right - WindowScreenPos.left;
	_windowWidth = ddSurfaceDesc2.dwWidth;
	ddSurfaceDesc2.dwHeight = WindowScreenPos.bottom - WindowScreenPos.top;
	_windowHeight = ddSurfaceDesc2.dwHeight;

	if (FAILED(iDirectDraw7Interface->CreateSurface(&ddSurfaceDesc2, &iDirectDrawSurface7_BackBuffer, nullptr)))
		throw std::exception("error: failed to create backbuffer");

	unknown122 = false;

	ZeroMemory(&ddSurfaceDesc2, sizeof ddSurfaceDesc2);
	ddSurfaceDesc2.dwSize = sizeof ddSurfaceDesc2;

	if (FAILED(iDirectDrawSurface7_BackBuffer->GetSurfaceDesc(&ddSurfaceDesc2)))
		throw std::exception("error: failed to get surface descriptor");

	Color545Struct ccs = { };
	ColorUtilities::ConvertRGBTo545Format(&ccs, ddSurfaceDesc2.ddpfPixelFormat.dwRBitMask,
		ddSurfaceDesc2.ddpfPixelFormat.dwGBitMask, ddSurfaceDesc2.ddpfPixelFormat.dwBBitMask);

	surfacePitch = ddSurfaceDesc2.lPitch;

	_surfaceDD7 = new SurfaceDD7(iDirectDrawSurface7_BackBuffer);
	IDirectDrawClipper* clipper = nullptr;
	if (FAILED(iDirectDraw7Interface->CreateClipper(NULL, &clipper, nullptr)))
		throw std::exception("error: failed to create directdraw clipper");

	clipper->SetHWnd(NULL, hWnd);
	iDirectDrawSurface7_Primary->SetClipper(clipper);
	clipper->Release();

	if (FAILED(iDirectDraw7Interface->QueryInterface(IID_IDirect3D7, reinterpret_cast<LPVOID*>(&_direct3D7))))
		throw std::exception("error: failed to query idirect3d7");

	if (FAILED(_direct3D7->CreateDevice(*lpGuid, iDirectDrawSurface7_BackBuffer, &_direct3DDevice7)))
		throw std::exception("error: failed to create direct3d7 device");

	DWORD width = WindowRect.right - WindowRect.left;
	DWORD height = WindowRect.bottom - WindowRect.top;
	_D3DVIEWPORT7 viewport = { 0, 0, width, height, 0.0, 1.0 };

	if (FAILED(_direct3DDevice7->SetViewport(&viewport)))
		throw std::exception("error: failed to set viewport of direct3d7 device");

	unknown12 = true;
	QueryPerformance::Get().QueryFrequencyAndCounter();

	RECT source = { 0,0,640,360 };
	RECT destination = { 0, 75, 800, 525 };

	QueryPerformance::Get().QueryCounter();
	_canPresent = true;

	// TODO: wtf is going on here? understanding this some more!
	int v42 = 10;
	do
	{
		Present(&source, &destination);
		--v42;
	} while (v42);

	auto frameStretchTime = QueryPerformance::Get().GetFrameStretchTime();
	if (frameStretchTime <= 0.2)
		_canPresent = true;
	else
		_canPresent = false;

	sub_1000D2D0(0, 0);
}

// TODO: this function is ugly, make it pretty!
void DrawBitmapDD7::Present(RECT* sourceRect, RECT* destinationRect)
{
	if (!unknown12)
		throw std::exception("error: unknown 12 is not true!");

	while (true)
	{
		HRESULT returnCode;
		do
		{
			if (unknown122)
			{
				if (!sourceRect)
					if (SUCCEEDED(returnCode = iDirectDrawSurface7_Primary->Flip(nullptr, NULL)))
						return;
			}
			else if (!sourceRect)
				if (SUCCEEDED(returnCode = iDirectDrawSurface7_Primary->Blt(&WindowScreenPos, iDirectDrawSurface7_BackBuffer, nullptr, DDBLT_WAIT, nullptr)))
					return;

			if (_canPresent)
			{
				RECT dest = RECT{ WindowScreenPos.left + destinationRect->left, WindowScreenPos.top + destinationRect->top,
				WindowScreenPos.left + destinationRect->right, WindowScreenPos.top + destinationRect->bottom };

				returnCode = iDirectDrawSurface7_Primary->Blt(destinationRect, iDirectDrawSurface7_BackBuffer, sourceRect, DDBLT_WAIT, nullptr);
			}else
			{
				returnCode = iDirectDrawSurface7_Primary->Blt(destinationRect, iDirectDrawSurface7_BackBuffer, sourceRect, DDBLT_WAIT, nullptr);
			}

			if (SUCCEEDED(returnCode))
				return;
		} while (0x00 == DDERR_SURFACEBUSY);

		if (returnCode == DDERR_SURFACELOST)
			break;
		if (returnCode != DDERR_WASSTILLDRAWING)
			throw std::exception("error: encountered a direct draw exception");
	}

	if (FAILED(iDirectDrawSurface7_BackBuffer->Restore()))
		throw std::exception("error: failed to restore backbuffer");
	if (FAILED(iDirectDrawSurface7_Primary->Restore()))
		throw std::exception("error: failed to restore primary");
}

int DrawBitmapDD7::sub_1000D2D0(uint32_t a1, uint32_t a2)
{
	if (a2 == 1)
		return 0;
	if (a2)
		throw std::exception("error: unknown exception");
	return 1;
}
