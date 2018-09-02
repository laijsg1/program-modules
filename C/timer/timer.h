#pragma once
#include<ctime>
#include<iostream>
using namespace std;
class Timer
{
public:
	Timer();
	~Timer();
	void setstart();
	bool gap(int gap);
	int getgap();
private:
	double reg_time;
	double sum_time;
	clock_t start;
	clock_t finish;
	
};

