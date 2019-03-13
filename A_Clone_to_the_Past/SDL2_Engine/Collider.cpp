// Nils Jungjohann

#include "Collider.h"

#include "Rect.h"

Collider::Collider(Rect* _pRect, Rect* _pParent, ECollisionType _colType)
{
	m_pRect = _pRect;
	m_pParent = _pParent;
	m_colType = _colType;
}

Collider::~Collider()
{
	delete m_pRect;
}

Rect* Collider::GetRect()
{
	Rect rect = Rect(m_pRect->w, m_pRect->h);

	rect.x = m_pParent->x + m_pRect->x;
	rect.y = m_pParent->y + m_pRect->y;

	return &rect;
}