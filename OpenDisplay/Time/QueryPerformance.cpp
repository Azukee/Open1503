#include "QueryPerformance.h"

QueryPerformance::QueryPerformance(SingletonLock)
{
	_frequency = LARGE_INTEGER{ };
	_performanceCounter = LARGE_INTEGER{ };
}

void QueryPerformance::QueryFrequencyAndCounter()
{
	QueryFrequency();
	QueryCounter();
}

void QueryPerformance::QueryFrequency()
{
	QueryPerformanceFrequency(&_frequency);
}

void QueryPerformance::QueryCounter()
{
	QueryPerformanceCounter(&_performanceCounter);
}

double QueryPerformance::GetFrameStretchTime() const
{
	LARGE_INTEGER performanceCount;
	QueryPerformanceCounter(&performanceCount);
	
	return static_cast<double>(performanceCount.QuadPart - _performanceCounter.QuadPart) / _frequency.QuadPart;
}

LARGE_INTEGER QueryPerformance::GetFrequency() const
{
	return _frequency;
}

LARGE_INTEGER QueryPerformance::GetPerformanceCounter() const
{
	return _performanceCounter;
}