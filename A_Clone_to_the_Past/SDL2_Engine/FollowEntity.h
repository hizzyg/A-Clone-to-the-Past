// Nils Jungjohann

#pragma once
#include "Actor.h"
#include "Animation.h"

class Point;

enum EState 
{
	FOLLOW,
	ATTACK,
	WAIT
};

class FollowEntity :
	public Actor
{
public:
	// constructor
	FollowEntity(Renderer* _pRenderer, const char* _pFileName,
		Rect* _pRect, Collider* _pCollider, Actor* _pTarget);

	// destructor
	~FollowEntity();

	// set target reference
	inline void SetTargetActor(Actor* _pActor) { m_pTarget = _pActor; };

	// update every frame
	virtual void Update(float _deltaTime) override;

	// render frame frame
	virtual void Render(Renderer* _pRenderer) override;

private:
	// target position
	Point* m_pTargetPos;

	// current state
	EState m_state = EState::FOLLOW;

	// offset x
	int m_xOffset = 64;

	// offset y
	int m_yOffset = 64;

	// followed actor
	Actor* m_pTarget;

	// follow target
	void Follow();

	// current animation
	Animation* m_pCurrentAnim;

	// idle animations
	Animation* m_pIdleFront;
	Animation* m_pIdleBack;
	Animation* m_pIdleLeft;
	Animation* m_pIdleRight;

	// move animations
	Animation* m_pMoveFront;
	Animation* m_pMoveBack;
	Animation* m_pMoveLeft;
	Animation* m_pMoveRight;
};