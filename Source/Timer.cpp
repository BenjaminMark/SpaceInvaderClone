#include "Timer.h"
#include "SDL.h"


Timer::Timer() : startTime(0)
{
}


Timer::~Timer()
{
}

void Timer::start()
{
	startTime = SDL_GetTicks();
}

uint32_t Timer::getTicks()
{
	return SDL_GetTicks() - startTime;
}
