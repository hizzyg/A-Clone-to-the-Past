#pragma once
#include "Actor.h"
#include "Macros.h"
#include "Engine.h"
#include <list>

class Scene;
class Sound;
class Animation;

class Player : public Actor
{
public:
	// constructor
	Player(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect, Collider* _pCollider);

	// destructor
	~Player();
	
	// update every frame
	virtual void Update(float _deltaTime) override;

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	// check collision
	void CheckMoveable(std::list<TexturedEntity*> _pEntities, float _deltaTime);

	// set moveable
	inline void SetMoveable(bool _moveable) 
		{ m_isMoveable = _moveable; };

	// get current scene
	inline Scene* GetScene() { return m_pScene; };

	// set current scene
	inline void SetScene(Scene* _pScene) { m_pScene = _pScene; };

	// get bullet texture
	inline Texture* GetBulletTexture() { return m_pBulletTexture; };

	// take damage
	inline void TakeDamage(int _damage) 
	{
		// decrease health
		m_health -= _damage;
	};

	// increase health
	inline void IncreaseHealth(int _health)
	{
		m_health += _health;
		if (m_health > m_maxHealth)
			m_health = m_maxHealth;
	}

	// get stamina
	inline float GetStamina() { return m_run; };

	// get max stamina
	inline float GetMaxStamina() { return m_maxRun; };

	// set stamina
	inline void SetStamina(int _run) { m_run = _run; };

	// get gold
	inline int GetGold() { return m_Gold; };

	// increase gold
	inline void IncreaseGold() { m_Gold++; };

	// decrease gold
	inline void DecreaseGold() { m_Gold--; };

	// get health
	inline int GetHealth() { return m_health; };

	// get max health
	inline int GetMaxHealth() { return m_maxHealth; };

	// return if bow is in hand
	inline bool HasBowInHand() { return m_isKeyActive; };

	// get sound
	inline Sound* GetShotSound() { return m_pShotSound; };
	
private:
	// is moveable
	bool m_isMoveable = true;

	// player hits
	bool m_playerHits = false;

	// is m_isKeyActive
	bool m_isKeyActive = true;

	// health
	int m_health = 10;

	// max health
	int m_maxHealth = 10;

	// run value
	float m_run = 100.0f;

	// max run
	float m_maxRun = 100.0f;

	// gold
	int m_Gold = 0;

	// bullet texture
	Texture* m_pBulletTexture;

	// current animation
	Animation* m_pCurrentAnim;

	// move down animation animation
	Animation* m_pMoveDown;

	// move right animation animation
	Animation* m_pMoveRight;

	// move left animation animation
	Animation* m_pMoveLeft;

	// move up animation animation
	Animation* m_pMoveUp;

	// shot sound
	Sound* m_pShotSound;

	// sword sound
	// Hasan Sahin
	Sound* m_pSwordSound;

	// current scene
	Scene* m_pScene;
};