#pragma once
#include <cstdint>

struct Color545Struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint32_t Representation545;
};

class ColorUtilities 
{
public:
	static uint32_t ConvertRGBTo545Format(Color545Struct* ccs, uint32_t r, uint32_t g, uint32_t b);
};

