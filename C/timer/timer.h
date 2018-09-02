#include "stdafx.h"
#include "Timer.h"
#include<cmath>

Timer::Timer()
{
	start = clock();
}


Timer::~Timer()
{
}

void Timer::setstart()
{
	start = clock();
}

bool Timer::gap(int gap)
{
	finish = clock();
	double duration = (double)(finish - start);
	while (duration - gap > 10)
		duration -= 10;
	if (abs(duration - gap) <= 10)
	{
		start = finish;
		return true;
	}
	else
		return false;
}

int Timer::getgap()
{
	finish = clock();
	int duration = finish - start;
	start = finish;
	return duration;
}
