#pragma once
#include <Windows.h>
#include <Architecture/Singleton.hpp>

struct TimingStuff
{
	LARGE_INTEGER Frequency;
	LARGE_INTEGER Counter;
};


class QueryPerformance : public Singleton<QueryPerformance>
{
public:
	QueryPerformance(SingletonLock);

	LONGLONG sub_10070A20(TimingStuff* timingStuff);
	int sub_10070A60(TimingStuff* timingStuff);
};