// Nils Jungjohann

#include "FollowEntity.h"
#include "Rect.h"
#include "Renderer.h"
#include <cstdlib>
#include <math.h>

FollowEntity::FollowEntity(Renderer * _pRenderer, const char * _pFileName, 
	Rect * _pRect, Collider* _pCollider, Actor* _pTarget)
	: Actor(_pRenderer, _pFileName, _pRect, _pCollider)
{
	m_pTarget = _pTarget;

	m_speed = m_pTarget->GetSpeed();

	m_pIdleFront = new Animation(0, 0, 32, 32, 10);
	m_pIdleFront->SetAnimationSpeed(1);

	m_pIdleBack = new Animation(0, 32, 32, 32, 10);
	m_pIdleBack->SetAnimationSpeed(1);

	m_pIdleLeft = new Animation(0, 64, 32, 32, 10);
	m_pIdleLeft->SetAnimationSpeed(1);

	m_pIdleRight = new Animation(0, 96, 32, 32, 10);
	m_pIdleRight->SetAnimationSpeed(1);

	m_pMoveBack = new Animation(0, 128, 32, 32, 8);
	m_pMoveBack->SetAnimationSpeed(0.4);

	m_pMoveFront = new Animation(0, 160, 32, 32, 8);
	m_pMoveFront->SetAnimationSpeed(0.4);

	m_pMoveLeft = new Animation(0, 192, 32, 32, 8);
	m_pMoveLeft->SetAnimationSpeed(0.4);

	m_pMoveRight = new Animation(0, 224, 32, 32, 8);
	m_pMoveRight->SetAnimationSpeed(0.4);

	m_pCurrentAnim = m_pIdleFront;
}

FollowEntity::~FollowEntity()
{
	// delete animations
	delete m_pIdleFront;
	delete m_pIdleBack;
	delete m_pIdleLeft;
	delete m_pIdleRight;
	delete m_pMoveFront;
	delete m_pMoveBack;
	delete m_pMoveLeft;
	delete m_pMoveRight;
}

void FollowEntity::Update(float _deltaTime)
{
	// return here for better visual
	if (!m_pTarget)
		return;

	switch (m_state)
	{
	case FOLLOW:
		Follow();
		break;
	case ATTACK:
		break;
	case WAIT:
		if (m_pCurrentAnim == m_pMoveFront)
			m_pCurrentAnim = m_pIdleFront;
		else if (m_pCurrentAnim == m_pMoveBack)
			m_pCurrentAnim = m_pIdleBack;
		else if (m_pCurrentAnim == m_pMoveLeft)
			m_pCurrentAnim = m_pIdleLeft;
		else if (m_pCurrentAnim == m_pMoveRight)
			m_pCurrentAnim = m_pIdleRight;

		if (abs(m_pRect->GetCenterPoint()->x - m_pTarget->GetRect()->GetCenterPoint()->x - UNIT) > UNIT ||
			abs(m_pRect->GetCenterPoint()->y - m_pTarget->GetRect()->GetCenterPoint()->y - UNIT) > UNIT) 
			m_state = EState::FOLLOW;
		break;
	}

	if (m_pCurrentAnim)
		m_pCurrentAnim->Update(_deltaTime);

	Actor::Update(_deltaTime);
}

void FollowEntity::Render(Renderer * _pRenderer)
{
	// if animation exists render with source rect
	if (m_pCurrentAnim)
		_pRenderer->RenderTexture(m_pTexture, m_pRect,
			&Rect(&m_pCurrentAnim->GetCurrentTexture(), m_pCurrentAnim->GetWidth(),
				m_pCurrentAnim->GetHeight()), 0, true);

	// render without source rect
	else
		Actor::Render(_pRenderer);
}

void FollowEntity::Follow()
{
	// if entity is too far away from target
	if (m_pRect->GetCenterPoint()->y < m_pTarget->GetRect()->GetCenterPoint()->y - UNIT)
	{
		m_yMovement = 1;
		m_pCurrentAnim = m_pMoveFront;
	}
	else if (m_pRect->GetCenterPoint()->y > m_pTarget->GetRect()->GetCenterPoint()->y + UNIT)
	{
		m_yMovement = -1;
		m_pCurrentAnim = m_pMoveBack;
	}

	if (m_pRect->GetCenterPoint()->x < m_pTarget->GetRect()->GetCenterPoint()->x - UNIT)
	{
		m_xMovement = 1;
		m_pCurrentAnim = m_pMoveRight;
	}
	else if (m_pRect->GetCenterPoint()->x > m_pTarget->GetRect()->GetCenterPoint()->x + UNIT)
	{
		m_xMovement = -1;
		m_pCurrentAnim = m_pMoveLeft;
	}

	if (m_pTarget->GetSpeed() > m_speed)
		m_speed = m_pTarget->GetSpeed();

	if (m_xMovement == 0 && m_yMovement == 0)
	{
		m_state = EState::WAIT;
		m_speed = m_pTarget->GetSpeed();
	}
}