#pragma once
#include <Windows.h>
#include <Architecture/Singleton.hpp>

#include <d3d.h>

class D3DXHandler : public Singleton<D3DXHandler>
{
public:
	D3DXHandler(SingletonLock) { }

	int sub_1000C7A0(IDirectDrawSurface7* surface, RECT* a2, int a3);
};