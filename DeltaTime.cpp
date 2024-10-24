#include "DeltaTime.h"
void DeltaTime::start()
{
	startTime = std::chrono::high_resolution_clock::now();
}

int DeltaTime::getdT()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
}
