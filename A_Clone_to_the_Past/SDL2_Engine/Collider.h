// Nils Jungjohann

#pragma once

class Rect;

enum ECollisionType
{
	MOVE,
	WALL,
	FLOOR,
	BULLET,
	TRIGGER
};

class Collider
{
public:
	// constructor
	Collider(Rect* _pRect, Rect* _pParent, ECollisionType _colType);

	// destructor
	~Collider();

	// get rect
	Rect* GetRect();

	// set rect
	inline void SetRect(Rect* _pRect) { m_pRect = _pRect; };

	// get collision type
	inline ECollisionType GetColType() { return m_colType; };

	// set collision type
	inline void SetColType(ECollisionType _colType) { m_colType = _colType; };

private:
	// parent rect
	Rect* m_pParent;

	// rect for offset and bounds 
	Rect* m_pRect;

	// collision type
	ECollisionType m_colType;
};