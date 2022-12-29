#pragma once
#include <Windows.h>
#include <ddraw.h>
#include <d3d.h>

class DrawBitmapDD7
{
	RECT WindowRect;
	RECT* WindowScreenPos;
	int unknown8;
	POINT* ScreenPoint;
	int backBufferCount_maybe;
	int unknown12;
	int unknown122;
	int unknown12222;
	int surfacePitch;
	int unknown1222;
	//tSurfaceDD7* surfaceDD7;
	int unknown14;
	IDirectDraw7* iDirectDraw7Interface;
	int unknown16;
	int unknown17;
	IDirectDrawSurface7* iDirectDrawSurface7_Primary;
	IDirectDrawSurface7* iDirectDrawSurface7_BackBuffer;
	char field_54;
	unsigned char gap[7];
	int windowWidth_CHECK;
	int windowHeight_CHECK;
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
	virtual void sub_1000C9F0(HWND hWnd, GUID* id, const GUID* lpGuid, tagRECT* a5);/*
	virtual void sub_1000C850();
	virtual void sub_1000CFE0();
	virtual void sub_1000D290();
	virtual void sub_1000C680();
	virtual void sub_1000C5A0();
	virtual void sub_1000B9D0();
	virtual void sub_1000D2D0();
	virtual void sub_1000D2A0();
	virtual void sub_1000D070();
	virtual void sub_1000C580();
	virtual void sub_1000C900();
	virtual void sub_1000C9E0();
	virtual void sub_1000D3C0();
	virtual void sub_1000C5E0();*/
};