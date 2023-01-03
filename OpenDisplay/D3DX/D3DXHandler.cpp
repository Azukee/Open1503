#include "D3DXHandler.h"

int D3DXHandler::sub_1000C7A0(IDirectDrawSurface7* surface, RECT* a2, int a3)
{
	DDBLTFX fx = { };
	fx.dwSize = sizeof fx;
	fx.dwAlphaDestConst = a3;

	HRESULT returnValue;
	if (SUCCEEDED(returnValue = surface->Blt(a2, nullptr, nullptr, DDBLT_WAIT | DDBLT_COLORFILL, &fx)))
		return 0;

	while (returnValue == DDERR_SURFACELOST)
	{
		if (FAILED(surface->Restore()))
			throw std::exception("error: failed to restore surface");

		do
		{
			if (SUCCEEDED(returnValue = surface->Blt(a2, nullptr, nullptr, DDBLT_WAIT | DDBLT_COLORFILL, &fx)))
				return 0;
		} while (returnValue == DDERR_WASSTILLDRAWING);
		
	}

	throw std::exception("error: sub_1000C7A0 failed");
}