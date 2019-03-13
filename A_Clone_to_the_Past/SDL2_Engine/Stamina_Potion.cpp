// Hasan Sahin

#include "Stamina_Potion.h"
#include "Player.h"

Stamina_Potion::Stamina_Potion(Renderer * _pRenderer, const char * _pFileName,
	Rect * _pRect, Collider* _pCollider)
	: Pickup(_pRenderer, _pFileName, _pRect, _pCollider)
{
}

Stamina_Potion::~Stamina_Potion()
{
}

void Stamina_Potion::Render(Renderer * _pRenderer)
{
	Pickup::Render(_pRenderer);
}

bool Stamina_Potion::Trigger(Player* _pPlayer)
{
	if (!(_pPlayer->GetStamina() == _pPlayer->GetMaxStamina()))
	{
		_pPlayer->SetStamina(_pPlayer->GetMaxStamina());
		Pickup::Trigger(_pPlayer);
	}

	return false;
}
