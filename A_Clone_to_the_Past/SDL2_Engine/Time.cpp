#include "Time.h"

float Time::m_deltaTime = 0;
int Time::m_fps = 0;

Time::Time()
{
	// get current time
	m_lastUpdate = clock();

	// set frames und time since last update
	m_framesSinceLastTimeStamp = 0;
	m_timeSinceLastTimeStamp = 0;
}

void Time::Update()
{
	// current time
	clock_t now = clock();

	// difference to last frame
	clock_t dif = now - m_lastUpdate;

	// set delta time
	m_deltaTime = dif / (float)CLOCKS_PER_SEC;

	// set last update
	m_lastUpdate = now;

	// increase frames since last time tamp
	m_framesSinceLastTimeStamp++;

	// increase time since last time stamp
	m_timeSinceLastTimeStamp += dif;

	// time since last time stamp > clocks per second
	if (m_timeSinceLastTimeStamp > CLOCKS_PER_SEC)
	{
		// set fps
		m_fps = m_framesSinceLastTimeStamp;

		// reset frames since last time stamp
		m_framesSinceLastTimeStamp = 0;

		// decrease time since time stamp
		m_timeSinceLastTimeStamp -= CLOCKS_PER_SEC;
	}
}