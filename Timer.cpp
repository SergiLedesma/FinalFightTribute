#include "Timer.h"
#include "SDL\include\SDL_timer.h"



Timer::Timer()
{
}


Timer::~Timer()
{
}

bool Timer::Start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();

	return true;
}

int Timer::GetTicks()
{
	if (started == true) {
		if (paused == true)
		{
			return pausedTicks;
		}
		else
		{
			return SDL_GetTicks() - startTicks;
		}
	}

	return NULL;
}

void Timer::Pause()
{
	if ((started == true) && (paused == false)) {
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::Unpause()
{
	if (paused == true) {
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

bool Timer::IsStarted()
{
	return started;
}

bool Timer::IsPaused()
{
	return paused;
}