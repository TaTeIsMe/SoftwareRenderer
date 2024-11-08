#include "TimerHandler.h"
#include <iomanip>
void TimerHandler::printFrameRate(std::ostream& os, float period)
{
	static unsigned int frames = 0;
	frames++;
	static auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();

	float seconds = std::chrono::duration_cast<std::chrono::duration<float>>(end - start).count();
	if (seconds > period)
	{
		float spf = seconds / frames;
		os
			<< frames << " frames in "
			<< std::setprecision(1) << std::fixed << seconds << " seconds = "
			<< std::setprecision(1) << std::fixed << 1.0f / spf << " FPS ("
			<< std::setprecision(3) << std::fixed << spf * 1000.0f << " ms/frame)\n";
		frames = 0;
		start = end;
	}
}

void TimerHandler::addTimers(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		timers.push_back(std::chrono::steady_clock::now());
	}
}

void TimerHandler::startTimer(int index)
{
	timers[index] = std::chrono::steady_clock::now();
}

void TimerHandler::printTimer(int index, string messege, std::ostream& os) const
{
	os << messege<< " " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - timers[index]).count() << "\n";
}

std::chrono::nanoseconds TimerHandler::getTimePassed(int index) const
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - timers[index]);
}
