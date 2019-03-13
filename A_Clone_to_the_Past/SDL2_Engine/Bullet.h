#pragma once
#include "Actor.h"

class Bullet : public Actor
{
public:
	// constructor
	Bullet(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect,
		Collider* _pCollider, int _xDirection, int _yDirection);
	
	// update every frame
	virtual void Update(float _deltaTime) override;

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

private:
	// direction x
	int m_xDirection;

	// direction y
	int m_yDirection;
};