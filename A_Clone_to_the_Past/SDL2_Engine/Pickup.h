// Nils Jungjohann

#pragma once
#include "TexturedEntity.h"

class Pickup
	: public TexturedEntity
{
public:
	// constructor
	Pickup(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect, Collider* _pCollider);

	// destructor
	~Pickup();

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	virtual bool Trigger(Player* _pPlayer) override;
};