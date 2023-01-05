#include "QueryPerformance.h"

LONGLONG QueryPerformance::sub_10070A20(TimingStuff* timingStuff)
{
	if (!timingStuff->Frequency.LowPart)
		throw std::exception("error: frequency not set!");
	LARGE_INTEGER performanceCount;
	QueryPerformanceCounter(&performanceCount);

	return 1000 * performanceCount.QuadPart / timingStuff->Frequency.LowPart;
}

int QueryPerformance::sub_10070A60(TimingStuff* timingStuff)
{

}