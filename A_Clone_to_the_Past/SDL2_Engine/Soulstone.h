// Hasan Sahin

#pragma once
#include "Pickup.h"

class Soulstone :
	public Pickup
{
public:
	// constructor
	Soulstone(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect, Collider* _pCollider);

	// destructor
	~Soulstone();

	// render every frame
	void Render(Renderer* _pRenderer) override;

	// trigger
	bool Trigger(Player* _pPlayer) override;
};