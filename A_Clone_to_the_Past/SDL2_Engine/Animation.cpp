#include "Animation.h"
#include "Point.h"
#include "Macros.h"


Animation::Animation(int _startX, int _startY, int _width, int _height,
	int _numberOfTextures)
{
	m_startX = _startX;
	m_startY = _startY;
	m_width = _width;
	m_height = _height;
	m_numberTextures = _numberOfTextures;
}

void Animation::Update(float _deltaTime)
{
	// increase time
	m_time += _deltaTime;

	// if time is lower than animation / count return
	if (m_time < m_animationSpeed / m_numberTextures)
		return;

	// increase current counter
	m_current++;

	// if current higher than number of textures
	if (m_current > m_numberTextures)
		m_current = 1;

	// reset time
	m_time = 0;
}

Point Animation::GetCurrentTexture()
{
	// new Point with current position
	Point p = Point(m_startX + m_width * (m_current - 1), m_startY);

	return p;
}