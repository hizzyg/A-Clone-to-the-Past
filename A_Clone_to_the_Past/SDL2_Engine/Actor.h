#pragma once
#include "TexturedEntity.h"

class Actor :
	public TexturedEntity
{
public:
	// constructor
	Actor(Renderer* _pRenderer, const char* _pFileName, 
		Rect* _pRect, Collider* _pCollider);

	// destructor
	~Actor();

	// update every frame
	virtual void Update(float _deltaTime) override;

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	// get speed
	inline int GetSpeed() { return m_speed; };

	// set speed
	inline void SetSpeed(int _speed) { m_normalSpeed = _speed; };

	// add movement
	void AddMovement(int _x, int _y);

protected:
	// movement x
	int m_xMovement;

	// movement y
	int m_yMovement;

	// speed
	int m_speed;

	// normal speed
	int m_normalSpeed;

	// calculate angle
	void CalculateAngle();
};