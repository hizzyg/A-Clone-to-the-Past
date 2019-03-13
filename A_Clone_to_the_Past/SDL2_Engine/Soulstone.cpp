// Hasan Sahin

#include "Soulstone.h"
#include "Player.h"

Soulstone::Soulstone(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect, Collider* _pCollider)
	: Pickup(_pRenderer, _pFileName, _pRect, _pCollider)
{
}

Soulstone::~Soulstone()
{
}

void Soulstone::Render(Renderer * _pRenderer)
{
	Pickup::Render(_pRenderer);
}

bool Soulstone::Trigger(Player* _pPlayer)
{
	_pPlayer->IncreaseGold();

	Pickup::Trigger(_pPlayer);

	return false;
}