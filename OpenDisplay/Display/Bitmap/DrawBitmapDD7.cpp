#include "DrawBitmapDD7.h"

#include "../../Utilities/ColorUtilities.h"
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


}