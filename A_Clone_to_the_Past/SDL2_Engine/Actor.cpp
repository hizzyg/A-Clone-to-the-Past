#include "Actor.h"
#include "Rect.h"
#include "Renderer.h"

Actor::Actor(Renderer * _pRenderer, const char * _pFileName,
	Rect * _pRect, Collider* _pCollider)
	: TexturedEntity(_pRenderer, _pFileName, _pRect, _pCollider)
{
}

Actor::~Actor()
{
}

void Actor::Update(float _deltaTime)
{
	// absolute values of movement
	int x = std::abs((long)((m_xMovement) * m_speed * _deltaTime));
	int y = std::abs((long)((m_yMovement)* m_speed * _deltaTime));

	// negative movement x
	if (m_xMovement < 0)
		x = -x;

	// negative movement y
	if (m_yMovement < 0)
		y = -y;

	// add movement to rect
	m_pRect->x += x;
	m_pRect->y += y;

	// calculate angle
	CalculateAngle();

	// reset movement
	m_xMovement = 0;
	m_yMovement = 0;
}

void Actor::Render(Renderer * _pRenderer)
{
	// parent render
	// konkrete elternklasse angeben
	TexturedEntity::Render(_pRenderer);

	// direct render
	// _pRenderer->RenderTexture(m_pTexture, m_pRect, nullptr, m_angle);
}

void Actor::AddMovement(int _x, int _y)
{
	// set movement
	m_xMovement = _x;
	m_yMovement = _y;

	// calculate angle
	CalculateAngle();
}

void Actor::CalculateAngle()
{
	// set angle 0
	if (m_xMovement == 1 && m_yMovement == 0)
		m_angle = 0;

	// ifset angle 45
	if (m_xMovement == 1 && m_yMovement == 1)
		m_angle = 45;

	// set angle 90
	if (m_xMovement == 0 && m_yMovement == 1)
		m_angle = 90;

	// set angle 135
	if (m_xMovement == -1 && m_yMovement == 1)
		m_angle = 135;

	// set angle 180
	if (m_xMovement == -1 && m_yMovement == 0)
		m_angle = 180;

	// set angle 225
	if (m_xMovement == -1 && m_yMovement == -1)
		m_angle = 225;

	// set angle 270
	if (m_xMovement == 0 && m_yMovement == -1)
		m_angle = 270;

	// if right movement set angle 0
	if (m_xMovement == 1 && m_yMovement == -1)
		m_angle = 315 ;
}