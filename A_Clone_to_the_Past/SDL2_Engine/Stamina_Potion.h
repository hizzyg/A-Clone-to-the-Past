// Hasan Sahin

#pragma once
#include "Pickup.h"

class Stamina_Potion :
	public Pickup
{
public:
	// constructor
	Stamina_Potion(Renderer* _pRenderer,const char* _pFileName, 
		Rect* _pRect, Collider* _pCollider);

	// destructor
	~Stamina_Potion();

	// render every frame
	void Render(Renderer* _pRenderer) override;

	// trigger
	bool Trigger(Player* _pPlayer) override;
};

