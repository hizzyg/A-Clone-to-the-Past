// Hasan Sahin

#pragma once
#include "Pickup.h"


class Health_Potion :
	public Pickup
{
public:
	// constructor
	Health_Potion(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect, Collider* _pCollider);

	//destructor
	~Health_Potion();

	// render every frame
	void Render(Renderer* _pRenderer) override;

	// trigger
	bool Trigger(Player* _pPlayer) override;
};

