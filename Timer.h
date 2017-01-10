#pragma once
#include "Module.h"

class Timer : public Module
{
public:
	Timer();
	~Timer();

	bool Start();
	void Pause();
	void Unpause();

	int GetTicks();

	bool IsStarted();
	bool IsPaused();

private:
	int startTicks = 0;
	int pausedTicks = 0;
	bool paused = false;
	bool started = false;
};