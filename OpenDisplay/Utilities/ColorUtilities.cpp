#include "ColorUtilities.h"

uint32_t ColorUtilities::ConvertRGBTo545Format(Color545Struct* ccs, uint32_t r, uint32_t g, uint32_t b)
{
	for (ccs->r = 0; r; ++ccs->r)
		r &= r - 1;
	for (ccs->g = 0; g; ++ccs->g)
		g &= g - 1;
	for (ccs->b = 0; b; ++ccs->b)
		b &= b - 1;
	uint32_t col = ccs->r + ccs->g + ccs->b;

	col = ((col & ~0xFF) | (col > 0x10));
	--col;
	col = ((col & ~0xFF) | (col & 0xF0));

	const auto result = col + 0x20;

	ccs->Representation545 = result;
	return result;
}