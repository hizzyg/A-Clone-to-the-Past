// Hasan Sahin

#include "Health_Potion.h"
#include "Player.h"



Health_Potion::Health_Potion(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect, Collider* _pCollider)
	: Pickup(_pRenderer, _pFileName, _pRect, _pCollider)
{
}

Health_Potion::~Health_Potion()
{
}

void Health_Potion::Render(Renderer * _pRenderer)
{
	Pickup::Render(_pRenderer);
}

bool Health_Potion::Trigger(Player * _pPlayer)
{
	if (_pPlayer->GetHealth() < _pPlayer->GetMaxHealth())
	{
		_pPlayer->IncreaseHealth(5);

		Pickup::Trigger(_pPlayer);
	}

	return false;
}
