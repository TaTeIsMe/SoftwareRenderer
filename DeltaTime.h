#pragma once
#include <chrono>
class DeltaTime
{
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
public:
	void start();
	int getdT();
};

