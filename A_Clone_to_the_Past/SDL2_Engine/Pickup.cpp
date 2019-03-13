// Nils Jungjohann

#include "Pickup.h"

#include "Collider.h"
#include "Player.h"
#include "Rect.h"
#include "Scene.h"

Pickup::Pickup(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect, Collider* _pCollider)
	: TexturedEntity(_pRenderer, _pFileName, _pRect, _pCollider)
{
	m_pCollider = new Collider(new Rect(m_pRect->w, m_pRect->h),
		m_pRect, ECollisionType::TRIGGER);
}

Pickup::~Pickup()
{
}

void Pickup::Render(Renderer * _pRenderer)
{
	TexturedEntity::Render(_pRenderer);
}

bool Pickup::Trigger(Player * _pPlayer)
{
	_pPlayer->GetScene()->AddRemoveEntity(this);

	return false;
}