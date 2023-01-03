#pragma once
#include <Windows.h>
#include <ddraw.h>
#include <d3d.h>
#include "../Surface/SurfaceDD7.h"

class DrawBitmapDD7
{
	RECT WindowRect;
	RECT WindowScreenPos;
	int _someOffset;
	POINT* ScreenPoint;
	int backBufferCount_maybe;
	int unknown12;
	int unknown122;
	int unknown12222;
	int surfacePitch;
	int unknown1222;
	SurfaceDD7* _surfaceDD7;
	int unknown14;
	IDirectDraw7* iDirectDraw7Interface;
	IDirect3D7* _direct3D7;
	IDirect3DDevice7* _direct3DDevice7;
	IDirectDrawSurface7* iDirectDrawSurface7_Primary;
	IDirectDrawSurface7* iDirectDrawSurface7_BackBuffer;

	// TODO: this name is suspicious, reverse!
	bool _canPresent;
	unsigned char gap[7];
	int _windowWidth;
	int _windowHeight;
	HWND windowHandle;
public:
	DrawBitmapDD7();

	/*virtual void sub_10026AF0();
	virtual void sub_10026B20();
	virtual void sub_1000D320();
	virtual void sub_1001FF00();
	virtual void sub_1000D310();
	virtual void sub_1000A180();
	virtual void sub_100042C0();
	virtual void sub_10026B10();
	virtual void nullsub_2();
	virtual void sub_10007970();
	virtual void sub_1000D3B0();
	virtual void sub_1000D3A0();
	virtual void nullsub_4();
	virtual void nullsub_3();
	virtual void sub_1000D380();
	virtual void sub_1000D390();
	virtual void sub_1000C480();*/
	virtual void sub_1000C9F0(HWND hWnd, GUID* id, const GUID* lpGuid, tagRECT* a5);
	/*
	virtual void sub_1000C850();
	virtual void sub_1000CFE0();
	virtual void sub_1000D290();
	*/
	virtual void Present(RECT* sourceRect, RECT* destinationRect);
	/*
	virtual void sub_1000C5A0();
	virtual void sub_1000B9D0();
	*/
	virtual int sub_1000D2D0(uint32_t a1, uint32_t a2);
	/*
	virtual void sub_1000D2A0();
	virtual void sub_1000D070();
	virtual void sub_1000C580();
	virtual void sub_1000C900();
	virtual void sub_1000C9E0();
	virtual void sub_1000D3C0();
	virtual void sub_1000C5E0();*/
};