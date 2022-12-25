#include "Display.h"

Display::Display()
{
	drawBitmapDD7 = nullptr;
	unknown0 = 0;
	unknown1 = 0;
	unknown2 = 0;
	unknown3 = 0;
}

DrawBitmapDD7* Display::getDrawBitmapInstance()
{
	return drawBitmapDD7;
}

void Display::createDrawBitmapDD7()
{
	const auto bitmap = new DrawBitmapDD7();

	drawBitmapDD7 = bitmap;
}