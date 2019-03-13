#include "Enemy.h"

#include "Animation.h"
#include "Bullet.h"
#include "Collider.h"
#include "Helper.h"
#include "Macros.h"
#include "Physics.h"
#include "Rect.h"
#include "Renderer.h"
#include "Texture.h"

Enemy::Enemy(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect,
	Collider* _pCollider, const char * _phealthBarFileName)
	: Actor(_pRenderer, _pFileName, _pRect, _pCollider)
{
	m_pHealthBar = new TexturedEntity(_pRenderer, _phealthBarFileName, new Rect(64, 8), nullptr);

	// set tag
	m_pTag = ENEMY;

	// create distance check rect
	m_pDistanceRect = new Rect(704, 704);

	// animations
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

	// create collider
	m_pCollider = new Collider(new Rect(new Point(16), new Point(32)), 
		m_pRect, ECollisionType::MOVE);

	// create sound
	m_pShotSound = new Sound(nullptr);
}

Enemy::~Enemy()
{
	delete m_pHealthBar;
	
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

void Enemy::Update(float _deltaTime)
{
	// decrease time
	m_timeState -= _deltaTime;

	// switch states
	switch (m_state)
	{

	// idle
	case EEnemyState::IDLE:
		if (m_timeState < 0)
			ChangeState();
		break;

	// walk
	case EEnemyState::WALK:
		m_xMovement = m_directionX;
		m_yMovement = m_directionY;
		if (m_timeState < 0)
			ChangeState();
		break;

	// attack
	case EEnemyState::ATTACK:
		m_xMovement = m_directionX;
		m_yMovement = m_directionY;


		if (m_timeState <= 0)
		{
			// set time time
			m_timeState = 0.5f;

			// create new bullet with no texture!!!
			Bullet* bullet = new Bullet(nullptr, nullptr,
				new Rect(m_pRect->x + m_directionX * 70, m_pRect->y + m_directionY * 70,
					16, 16), nullptr, m_directionX, m_directionY);

			// set bullet texture
			bullet->GetTexture()->SetSDLTexture(m_pPlayer->GetBulletTexture()->GetSDLTexture());

			// add bullet to move entities list
			m_pPlayer->GetScene()->AddMoveEntity(bullet);

			// play shot sound
			m_pShotSound->Play();
		}
		break;
	default:
		break;
	}

	// update parent
	Actor::Update(_deltaTime);

	// get health bar rect
	Rect rect = *m_pHealthBar->GetRect();

	// set width rect
	rect.w = 64 * m_health / 100;

	// set x and y of rect
	rect.x = m_pRect->x;
	rect.y = m_pRect->y;

	// set rect of health bar
	m_pHealthBar->SetRect(&rect);

	// check distance to player
	CheckDistance();

	// update current animation
	if (m_pCurrentAnim)
		m_pCurrentAnim->Update(_deltaTime);
}

void Enemy::Render(Renderer * _pRenderer)
{
	// render health bar
	m_pHealthBar->Render(_pRenderer);

	// render with source rect

	// if animation exists render with source rect
	if (m_pCurrentAnim)
		_pRenderer->RenderTexture(m_pTexture, m_pRect,
		&Rect(&m_pCurrentAnim->GetCurrentTexture(), 
		m_pCurrentAnim->GetWidth(), m_pCurrentAnim->GetHeight()), 
		0 , true);

	// render without source rect
	else
		Actor::Render(_pRenderer);
}

void Enemy::CheckCollision(std::list<TexturedEntity*> _pEntities, float _deltaTime)
{
	// if not walking return
	if (m_state != EEnemyState::WALK)
		return;

	// next rect
	Rect nextRect = Rect(m_pCollider->GetRect());

	// increase location
	nextRect.x += m_directionX * m_speed * _deltaTime;
	nextRect.y += m_directionY * m_speed * _deltaTime;

	// if collision change state
	for each (TexturedEntity* entity in _pEntities)
	{
		if (entity == this ||
			!entity->GetCollider())
			continue;

		if ((entity->GetCollider()->GetColType() == ECollisionType::WALL ||
			entity->GetCollider()->GetColType() == ECollisionType::FLOOR ||
			entity->GetCollider()->GetColType() == ECollisionType::MOVE) &&
			Physics::RectRectCollision(&nextRect, entity->GetRect()))
		{
			ChangeState();
		}
	}
}

void Enemy::ChangeState()
{
	// set new time state
	m_timeState = 3.0f;

	// if idle set walk and random direction
	if (m_state == EEnemyState::IDLE)
	{
		if (m_pCurrentAnim == m_pMoveFront)
			m_pCurrentAnim = m_pIdleFront;
		else if (m_pCurrentAnim == m_pMoveBack)
			m_pCurrentAnim = m_pIdleBack;
		else if (m_pCurrentAnim == m_pMoveLeft)
			m_pCurrentAnim = m_pIdleLeft;
		else if (m_pCurrentAnim == m_pMoveRight)
			m_pCurrentAnim = m_pIdleRight;

		// set walk state
		m_state = EEnemyState::WALK;
		m_directionX = rand() % 3 - 1;
		m_directionY = rand() % 3 - 1;
	}

	// if walk set idle
	else
	{
		// set idle state
		m_state = EEnemyState::IDLE;
	}
}

void Enemy::CheckDistance()
{
	// set x and y of distance rect
	m_pDistanceRect->x = m_pRect->x - 320;
	m_pDistanceRect->y = m_pRect->y - 320;

	// if distance rect collides with player
	if (Physics::RectRectCollision(m_pDistanceRect, m_pPlayer->GetRect()))
	{
		// set state to attack
		m_state = EEnemyState::ATTACK;

		// set x direction
		if (m_pPlayer->GetRect()->x < m_pRect->x)
			m_directionX = -1;
		else if (m_pPlayer->GetRect()->x > m_pRect->x + 64)
			m_directionX = 1;
		else
			m_directionX = 0;

		// set y direction
		if (m_pPlayer->GetRect()->y < m_pRect->y)
			m_directionY = -1;
		else if (m_pPlayer->GetRect()->y > m_pRect->y + 64)
			m_directionY = 1;
		else
			m_directionY = 0;

		// set speed to 0
		m_speed = 0;
	}

	// if no collision and attack state is active
	else if (m_state == EEnemyState::ATTACK)
	{
		// change state
		ChangeState();

		// set speed
		m_speed = 100;
	}
}