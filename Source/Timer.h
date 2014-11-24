#pragma once

#include <stdint.h>

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	uint32_t getTicks(); //in ms

private:
	uint32_t startTime; 
};

