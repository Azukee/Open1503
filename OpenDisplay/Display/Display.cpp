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
	drawBitmapDD7 = new DrawBitmapDD7();
}

void Display::CreateDisplayInstance(bool unknown, Display** display)
{
	const auto displayInstance = new Display();
	displayInstance->createDrawBitmapDD7();
	*display = displayInstance;
}
