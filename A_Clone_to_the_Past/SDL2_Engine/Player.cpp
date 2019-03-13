#include "Player.h"
#include "Input.h"
#include "Rect.h"
#include "Physics.h"
#include "Scene.h"
#include "Bullet.h"
#include "Helper.h"
#include "Texture.h"
#include "Enemy.h"
#include "Sound.h"
#include "Animation.h"
#include "Renderer.h"
#include "Collider.h"

Player::Player(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect, Collider* _pCollider)
	: Actor(_pRenderer, _pFileName, _pRect, _pCollider)
{
	// create bullet texture
	m_pBulletTexture = new Texture(GetAssetPath("Texture/Bullet/T_Bullet.png", 5).c_str(),
		_pRenderer);

	// load shot sound
	m_pShotSound = new Sound(GetAssetPath("Sound/Sound/S_Shot.wav", 5).c_str());

	// load shoot sound
	m_pSwordSound = new Sound(GetAssetPath("Sound/Sound/S_Sword.wav", 5).c_str());

	// move animations
	m_pMoveDown = new Animation(0, 0, 32, 32, 6);
	m_pMoveUp = new Animation(0, 32, 32, 32, 6);
	m_pMoveRight = new Animation(0, 64, 32, 32, 4);
	m_pMoveLeft = new Animation(0, 96, 32, 32, 4);
	
	m_pMoveDown->SetAnimationSpeed(0.3f);
	m_pMoveUp->SetAnimationSpeed(0.3f);
	m_pMoveRight->SetAnimationSpeed(0.3f);
	m_pMoveLeft->SetAnimationSpeed(0.3f);

	m_pCurrentAnim = m_pMoveDown;

	// set tag
	m_pTag = PLAYER;

	// create collider
	m_pCollider = new Collider(new Rect(16, 16, 32, 48),
		m_pRect, ECollisionType::MOVE);
}

Player::~Player()
{
	delete m_pBulletTexture;
	delete m_pShotSound;

	// delete animations
	delete m_pMoveDown;
}

void Player::Update(float _deltaTime)
{
	// reset hits
	m_playerHits = false;

	// if not moveable return
	if (!m_isMoveable)
		return;

	// set animation to move right
	if (Input::GetKey(SDL_SCANCODE_D))
	{
		m_xMovement += 1;
		m_pCurrentAnim = m_pMoveRight;
	}

	// set animation to move down
	if (Input::GetKey(SDL_SCANCODE_S))
	{
		m_yMovement += 1;
		m_pCurrentAnim = m_pMoveDown;
	}

	// set animation to move left
	if (Input::GetKey(SDL_SCANCODE_A))
	{
		m_xMovement -= 1;
		m_pCurrentAnim = m_pMoveLeft;
	}

	// set animation to move up
	if (Input::GetKey(SDL_SCANCODE_W))
	{
		m_yMovement -= 1;
		m_pCurrentAnim = m_pMoveUp;
	}

	// if shift is pressed increase movement and decrease run time
	if (Input::GetKey(SDL_SCANCODE_F))
	{
		if (m_run <= 100 && m_run >= 0)
		{
			m_run -= 10 * _deltaTime;

			if (m_run > 0)
			{
				m_speed = m_normalSpeed * 2;
			}
		}
		else
		{
			m_speed = m_normalSpeed;
		}
	}
	else
	{
		// increase run time
		m_run += 10 * _deltaTime;
		if (m_run > 100.0f)
			m_run = 100.0f;

		// set speed to normal
		m_speed = m_normalSpeed;
	}

	// update rect
	Actor::Update(_deltaTime);

	// x direction
	int x = 0;

	// y direction
	int y = 0;

	// set x direction
	if (m_pCurrentAnim == m_pMoveRight)
		x = 1;
	else if (m_pCurrentAnim == m_pMoveLeft)
		x = -1;

	// set y direction
	if (m_pCurrentAnim == m_pMoveDown)
		y = 1;
	else if (m_pCurrentAnim == m_pMoveUp)
		y = -1;

	// if space is pressed down spawn bullet
	if (Input::GetKeyDown(SDL_SCANCODE_SPACE))
	{
		if (m_isKeyActive)
		{
			// create bullet
			Bullet* bullet = new Bullet(nullptr, nullptr,
				new Rect(m_pRect->x + x * UNIT + 16,
					m_pRect->y + y * UNIT + 16, 16, 16), nullptr, x, y);

			// add to list
			m_pScene->AddMoveEntity(bullet);

			// set texture of bullet
			bullet->GetTexture()->SetSDLTexture(m_pBulletTexture->GetSDLTexture());

			// play shot sound
			m_pShotSound->Play();
		}
		else
		{
			// set hits to true
			m_playerHits = true;

			// play sword sound
			m_pSwordSound->Play();
		}
	}

	// Hasan Sahin
	// change weapon
	if (Input::GetKeyDown(SDL_SCANCODE_Q))
	{
		if (m_isKeyActive)
		{
			m_isKeyActive = false;
		}
		else if (!m_isKeyActive)
		{
			m_isKeyActive = true;
		}
	}
	
	// update animation
	if (m_pCurrentAnim)
		m_pCurrentAnim->Update(_deltaTime);
}

void Player::Render(Renderer * _pRenderer)
{
	// x direction
	int x = 0;

	// y direction
	int y = 0;

	// set x direction
	if (m_pCurrentAnim == m_pMoveRight)
		x = 1;
	else if (m_pCurrentAnim == m_pMoveLeft)
		x = -1;

	// set y direction
	if (m_pCurrentAnim == m_pMoveDown)
		y = 1;
	else if (m_pCurrentAnim == m_pMoveUp)
		y = -1;

	// if animation exists render with source rect
	if (m_pCurrentAnim)
		_pRenderer->RenderTexture(m_pTexture, m_pRect,
			&Rect(&m_pCurrentAnim->GetCurrentTexture(), m_pCurrentAnim->GetWidth(),
				m_pCurrentAnim->GetHeight()), 0, true);

	// render without source rect
	else
		Actor::Render(_pRenderer);
}

void Player::CheckMoveable(std::list<TexturedEntity*> _pEntities, float _deltaTime)
{
	// rect after movement frame
	Rect* nextRect = new Rect(m_pCollider->GetRect()->x, m_pCollider->GetRect()->y,
		m_pCollider->GetRect()->w, m_pCollider->GetRect()->h);

	// save input
	int x = 0;
	int y = 0;

	// rotate player to 0
	if (Input::GetKey(SDL_SCANCODE_D))
		x = 1;

	// rotate player to 90
	if (Input::GetKey(SDL_SCANCODE_S))
		y = 1;

	// rotate player to 180
	if (Input::GetKey(SDL_SCANCODE_A))
		x = -1;

	// rotate player to 270
	if (Input::GetKey(SDL_SCANCODE_W))
		y = -1;

	// increase rect x and y
	nextRect->x += x * m_speed * _deltaTime;
	nextRect->y += y * m_speed * _deltaTime;

	// rect for hits
	Rect rect;
	rect.h = UNIT;
	rect.w = UNIT;
	
	// reset x and y
	x = 0;
	y = 0;
	
	// set x direction
	if (m_angle == 0 || m_angle == 45 || m_angle == 315)
		x = 1;
	else if (m_angle == 135 || m_angle == 180 || m_angle == 225)
		x = -1;
	
	// set y direction
	if (m_angle == 45 || m_angle == 90 || m_angle == 135)
		y = 1;
	else if (m_angle == 225 || m_angle == 270 || m_angle == 315)
		y = -1;
	
	// set hit rect position
	rect.x = m_pRect->x + x * 64;
	rect.y = m_pRect->y + y * 64;

	// check entities
	for each (TexturedEntity* entity in _pEntities)
	{
		if (!entity->GetCollider())
			continue;

		// check player moveable
		if ((entity->GetCollider()->GetColType() == ECollisionType::FLOOR ||
			entity->GetCollider()->GetColType() == ECollisionType::MOVE ||
			entity->GetCollider()->GetColType() == ECollisionType::WALL) &&
			Physics::RectRectCollision(nextRect, entity->GetCollider()->GetRect()))
		{
			m_isMoveable = false;
		}

		// if player hits
		if (m_playerHits)
		{
			if (entity->GetTag() != ENEMY)
				continue;

			// if hit rect collides with entity
			if (Physics::RectRectCollision(&rect, entity->GetCollider()->GetRect()))
				((Enemy*)entity)->TakeDamage(25);
		}

		if (entity->GetCollider()->GetColType() == ECollisionType::TRIGGER &&
			Physics::RectRectCollision(nextRect, entity->GetCollider()->GetRect()))
		{
			if (entity->Trigger(this))
				return;
		}
	}
}