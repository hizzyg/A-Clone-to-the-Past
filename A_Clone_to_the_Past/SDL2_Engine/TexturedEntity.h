#pragma once
#include "Entity.h"

class Collider;
class Rect;
class Texture;

class TexturedEntity : public Entity
{
public:
	// constructor
	TexturedEntity(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect, Collider* _pCollider);

	// destructor
	~TexturedEntity();

	// update every frame
	virtual void Update(float _deltaTime) override;

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	// trigger
	virtual bool Trigger(Player* _pPlayer) override;

	// get rect
	virtual Rect* GetRect() override;

	// set rect
	virtual void SetRect(Rect* _pRect) override;

	// get texture
	inline Texture* GetTexture() { return m_pTexture; };

	// get angle
	inline float GetAngle() { return m_angle; };

	// set angle
	inline void SetAngle(float _angle) { m_angle = _angle; };

	// get collider
	inline Collider* GetCollider() { return m_pCollider; };

	// set collider
	void SetCollider(Collider* _pCollider);

protected:
	// angle
	float m_angle;

	// texture
	Texture* m_pTexture;

	// rect
	Rect* m_pRect;

	// collider
	Collider* m_pCollider;
};