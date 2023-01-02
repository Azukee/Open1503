#include "SurfaceDD7.h"

#include <exception>

int SurfaceDD7::initFromDrawSurface()
{
	_drawSurface->AddRef();

	DDSURFACEDESC2 surfaceDescriptor = { };
	ZeroMemory(&surfaceDescriptor, sizeof surfaceDescriptor);

	surfaceDescriptor.dwSize = sizeof surfaceDescriptor;
	if (FAILED(_drawSurface->GetSurfaceDesc(&surfaceDescriptor)))
		throw std::exception("error: failed to get surface descriptor of back buffer");
	
	_surfaceHeight = surfaceDescriptor.dwHeight;
	_surfaceWidth = surfaceDescriptor.dwWidth;
	const uint32_t dwFlags = surfaceDescriptor.ddpfPixelFormat.dwFlags;

	const bool flag = (dwFlags & 0x40) == 0;
	if (!flag)
	{
		if ((dwFlags & 0x20) != 0)
		{
			// TODO: implement
		}else
		{
			ColorUtilities::ConvertRGBTo545Format(&_unknown4, surfaceDescriptor.ddpfPixelFormat.dwRBitMask,
				surfaceDescriptor.ddpfPixelFormat.dwGBitMask, surfaceDescriptor.ddpfPixelFormat.dwBBitMask);
		}
	}

	const int calculatedWidth = 8 * surfaceDescriptor.lPitch / _unknown4.Representation545;
	_calculatedWidth = calculatedWidth;
	return calculatedWidth;
}

SurfaceDD7::SurfaceDD7(IDirectDrawSurface7* backBuffer)
{
	_drawSurface = backBuffer;
	initFromDrawSurface();
	_unknown1 = 0;
}
