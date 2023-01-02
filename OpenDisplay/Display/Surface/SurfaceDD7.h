#pragma once
#include <cstdint>
#include <ddraw.h>
#include "../../Utilities/ColorUtilities.h"

class SurfaceDD7
{
	IDirectDrawSurface7* _drawSurface;
	int _unknown1;
	int16_t _surfaceWidth;
	int16_t _surfaceHeight;
	int _calculatedWidth;
	Color545Struct _unknown4;
	int _unknown5;

	int initFromDrawSurface();
public:
	SurfaceDD7(IDirectDrawSurface7* backBuffer);
	/*int sub_10026AF0;
	int sub_10026B20;
	int sub_100090B0;
	int anonymous_0;
	int sub_1001FF00;
	int sub_100090A0;
	int anonymous_1;
	int anonymous_2;
	int sub_1000A180;
	int sub_100042C0;
	int sub_10026B10;
	int nullsub_2;
	int sub_10007970;
	int anonymous_3;
	int anonymous_4;
	int anonymous_5;
	int anonymous_6;
	int nullsub_4;
	int sub_10009930;
	int anonymous_7;
	int sub_10009A10;
	int sub_10009A20;
	int sub_10009A30;
	int anonymous_8;
	int sub_100097F0;
	int anonymous_9;
	int anonymous_10;
	int anonymous_11;
	int anonymous_12;
	int sub_10009080;
	int sub_100091C0;
	int sub_100095F0;
	int sub_10009690;
	int sub_10009770;
	int sub_10009910;
	int anonymous_13;
	int sub_100099A0;
	int sub_100099B0;
	int sub_10009050;
	int tSurface_Reset_Boolean;*/
};

