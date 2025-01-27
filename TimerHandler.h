#pragma once
#include <iostream>
#include<vector>
#include<chrono>
using namespace std;

class TimerHandler
{
	vector<std::chrono::high_resolution_clock::time_point> timers;
	vector<int> times;
public:
	void printFrameRate(std::ostream& os = std::cout, float period = 2.0f);
	void addTimers(int amount);
	void startTimer(int index);
	void endTimer(int index);
	void printTimer(int index, string messege = "", std::ostream& os = std::cout);
	std::chrono::nanoseconds getTimePassed(int index)const ;
};

