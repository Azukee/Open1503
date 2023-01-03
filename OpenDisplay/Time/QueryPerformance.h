#pragma once
#include "../Utilities/Singleton.hpp"
#include <windows.h>

class QueryPerformance : public Singleton<QueryPerformance>
{
	LARGE_INTEGER _frequency;
	LARGE_INTEGER _performanceCounter;
public:
	QueryPerformance(SingletonLock);

	void QueryFrequency();
	void QueryCounter();
	void QueryFrequencyAndCounter();

	double GetFrameStretchTime() const;
	LARGE_INTEGER GetFrequency() const;
	LARGE_INTEGER GetPerformanceCounter() const;
};

