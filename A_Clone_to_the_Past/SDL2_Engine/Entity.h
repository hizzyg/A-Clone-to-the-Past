#pragma once

class Rect;
class Renderer;
class Player;

class Entity
{
public:
	// get rect
	virtual Rect* GetRect() = 0;

	// set rect
	virtual void SetRect(Rect* _pRect) = 0;

	// update every frame
	virtual void Update(float _deltaTime) = 0;

	// render every frame
	virtual void Render(Renderer* _pRenderer) = 0;

	// trigger
	virtual bool Trigger(Player* _pPlayer) = 0;

	// get tag
	inline char* GetTag() { return m_pTag; };

	// set tag
	inline void SetTag(char* _pTag) { m_pTag = _pTag; };

protected:
	// tag of entity
	char* m_pTag;
};