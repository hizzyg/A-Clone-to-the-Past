#pragma once
#include <time.h>

class Time
{
public:
	// conctructor
	Time();

	// update every frame
	void Update();

	// get time since last frame
	static inline float GetDeltaTime() { return m_deltaTime; };

	// get frames per seconds
	static inline int GetFPS() { return m_fps; };

private:
	// frames per soeconds
	static int m_fps;

	// delta time
	static float m_deltaTime;

	// frames since last time stamp
	int m_framesSinceLastTimeStamp;

	// last updated time point
	clock_t m_lastUpdate;

	// time since last time stamp clock_t
	clock_t m_timeSinceLastTimeStamp;
};