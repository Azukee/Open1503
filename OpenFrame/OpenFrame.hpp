#pragma once

enum Frame
{
	Startup = 5
};

class OpenFrame
{
public:
	static int CreateAnnoFrameInstance(Frame frameToConstruct, int a2, int* a3)
	{
		switch(frameToConstruct)
		{
		case Startup:

			break;
		}
	}
};