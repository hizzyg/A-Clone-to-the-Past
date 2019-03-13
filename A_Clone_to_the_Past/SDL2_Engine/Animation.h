#pragma once

class Point;

class Animation
{
public:
	// constructor
	Animation(int _startX, int _startY, int _width, int _height,
		int _numberOfTextures);

	// update
	void Update(float _deltaTime);

	// get current texture position
	Point GetCurrentTexture();

	// get width
	inline int GetWidth() { return m_width; };

	// get height
	inline int GetHeight() { return m_height; };

	// get animation speed
	inline float GetAnimationSpeed() { return m_animationSpeed; };

	// set animation speed
	inline void SetAnimationSpeed(float _speed) { m_animationSpeed = _speed; };

	// get animation percentage
	inline float GetAnimationPercentage() { return m_current / m_numberTextures * 100.0f; };

private:
	// start position
	int m_startX;

	// start position y
	int m_startY;

	// width single texture
	int m_width;

	// height single texture
	int m_height;

	// current texture counter
	int m_current = 1;

	// number of textures
	int m_numberTextures;
	
	// animation speed in seconds
	float m_animationSpeed;

	// current time
	float m_time = 0;
};