#pragma once
#include <Architecture/Singleton.hpp>
#include <windows.h>
#include <exception>

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

