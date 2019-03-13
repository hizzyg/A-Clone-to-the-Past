// Nils Jungjohann

#pragma once
#include "TexturedEntity.h"

class InteractiveEntity;

class TriggerEntity :
	public TexturedEntity
{
public:
	// constructor
	TriggerEntity(InteractiveEntity* _pInterEntity, Rect* _pRect, Collider* _pCollider);

	// update every frame
	void Update(float _deltaTime) override;

	// trigger
	virtual bool Trigger(Player* _pPlayer) override;

protected:
	// Interactive Entity
	InteractiveEntity* m_pInterEntity;

	// previous triggered
	bool m_lastTriggered = false;

	// now triggered
	bool m_nowTriggered = false;
};