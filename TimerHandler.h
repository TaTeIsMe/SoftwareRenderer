#pragma once
#include <iostream>
#include<vector>
#include<chrono>
using namespace std;

class TimerHandler
{
	vector<std::chrono::steady_clock::time_point> timers;
public:
	void printFrameRate(std::ostream& os = std::cout, float period = 2.0f);
	void addTimers(int amount);
	void startTimer(int index);
	void printTimer(int index, string messege = "", std::ostream& os = std::cout)const;
};

