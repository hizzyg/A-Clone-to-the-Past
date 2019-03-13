#include "Bullet.h"

#include "Collider.h"
#include "Rect.h"

Bullet::Bullet(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect,
	Collider* _pCollider, int _xDirection, int _yDirection)
	: Actor(_pRenderer, _pFileName, _pRect, _pCollider)
{
	// set directions
	m_xDirection = _xDirection;
	m_yDirection = _yDirection;

	// set speed
	m_speed = 500;

	// set collider Type
	m_pCollider = new Collider(new Rect(m_pRect->w, m_pRect->h),
		m_pRect, ECollisionType::BULLET);

	// calculate angle
	CalculateAngle();
}

void Bullet::Update(float _deltaTime)
{
	// update movement
	m_xMovement = m_xDirection;
	m_yMovement = m_yDirection;

	// update parent class
	Actor::Update(_deltaTime);
}

void Bullet::Render(Renderer * _pRenderer)
{
	// render parent class
	Actor::Render(_pRenderer);
}